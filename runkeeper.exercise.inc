<?php

/**
 * callback function for user/member-home
 */
function runkeeper_user_exercise_page(){
  $output = render(drupal_get_form('runkeeper_user_autocomplete_form'));
  $output .= runkeeper_exercise_page();
  return $output; 
}

function runkeeper_exercise_page(){
  global $user;
  $uid = (!empty($_SESSION['search_user']) && arg(0) == 'user') ? $_SESSION['search_user'] : $user->uid;
  $output = render(drupal_get_form('runkeeper_exercise_data_table',$uid));
  return $output;
}

function runkeeper_exercise_data_table($form, &$form_state, $uid){
  
  if(!empty($form_state['values'])){
    $week = $form_state['values']['filter'];
    $week = "-$week Week";
  }else{
    $week = '-1 Week';
  }
  
  $from = strtotime($week);
  $to   = time();
  watchdog('argument',current_path());
  
  $pid = _runkeeper_user_plan_id($uid);
  
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'workout_entry')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_date', 'value', array(date('Y-m-d H:i:s',$from), date('Y-m-d H:i:s',$to)), 'BETWEEN')
    ->fieldCondition('field_plan','nid', $pid)
    ->addTag('debug');

  $result = $query->execute();
  
  $plandata = array();
  if(!empty($result['node'])){
    foreach($result['node'] as $planid){
      $plan = node_load($planid->nid);
      $lang = $plan->language;
      
      $plandata[] = array(
        'nid' => $plan->nid,
        'title' => $plan->title,
        'type' => !empty($plan->field_workout_type[$lang]) ? $plan->field_workout_type[$lang][0]['value'] : 'strength_training',
        'date' => format_date(strtotime($plan->field_date[$lang][0]['value']),'custom','d-m-y'),
        'total_calories' => '',
      );
    }  
  }
  
  $strengthQuery = db_select('user_strength_activity','sa')
                      ->fields('sa',array('total_calories','uri','created','sid'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN');
                      
  $strengthResult = $strengthQuery->execute()->fetchAll();
  
  if(!empty($strengthResult)){
    foreach($strengthResult as $strengthRecord){    
      $strengthTitle = get_strength_activity_title($strengthRecord->sid);
      $plandata[] = array(
        'nid' => '',
        'title' => $strengthTitle,
        'type' => 'strength_traning',
        'date' => format_date($strengthRecord->created,'custom','d-m-y'),
        'uri' => 'user/'.$uid.'/strength-training'.$strengthRecord->uri,
        'total_calories' => $strengthRecord->total_calories,
      );
    }  
  }
  
  dpm($plandata);
  
  $fitnessQuery = db_select('user_fitness_activity','sa')
                      ->fields('sa',array('total_calories','uri','created','type', 'total_distance'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $fitnessResult = $fitnessQuery->fetchAll();
  
  if(!empty($fitnessResult)){
    foreach($fitnessResult as $fitnessRecord){
      $plandata[] = array(
        'nid' => '',
        'title' => $fitnessRecord->type .' '.$fitnessRecord->total_distance,
        'type' => strtolower($fitnessRecord->type),
        'date' => format_date($fitnessRecord->created,'custom','d-m-y'),
        'uri' => 'user/'.$uid.'/fitness-activities'.$fitnessRecord->uri,
        'total_calories' => $fitnessRecord->total_calories,
      );
    }  
  }

  $skip_key = array();
  foreach($plandata as $key => $plancontent){
		
    if(in_array($key,$skip_key)){
      unset($plandata[$key]);
      continue;
    }else{
       $searchdata = searchForKey($plancontent['date'], 'date', $plandata);
       
       if($searchdata){
        
         foreach($searchdata as $searchkey){
            $searches[$searchkey] = $plandata[$searchkey];
         }
         
         $searchdata = searchForKey($plancontent['type'], 'type', $searches);
         
         if($searchdata){
            foreach($searchdata as $searchkey){
                $skip_key[] = $searchkey;
            } 
         }
         
         if($skip_key){
            $plandata[$key] = workoutSumData($skip_key,$plandata); 
         } 
         
       }
          
    }
  }
  
  $row = array();
  foreach($plandata as $record){
    $url = !empty($record['nid']) ? 'node/'.$record['nid'] : $record['uri'];
    $calories = !empty($record['total_calories']) ? $record['total_calories'] : t('Missing'); 
    $row[] = array($record['date'],$record['title'],$calories,l('view details',$url));
  }
  
  $data = $row;
  
  $headers = array(t('Date'), t('Title'), t('Calories'),t(''));
  
  $table = theme('table', array(
      'header' => $headers, 
      'rows' => $data, 
      'empty' => t('No items found.'),
      'attributes' => array('class' => array('data-table'))
    )
  );
  $form = array();
  
  $form['filter'] = array(
    '#type' => 'select',
    '#title' => t('week'),
    '#options' => array(
      '1' => t('Last 1 week'),
      '2' => t('Last 2 weeks'),
      '3' => t('Last 3 weeks'),
      '4' => t('Last 4 weeks'),
    ),
    '#ajax' => array(
        'event' => 'change',
        'wrapper' => 'squadron-mitesh',
        'callback' => '_exercise_data_ajax_callback',
        'method' => 'replace',
     ),
    '#default_value' => !empty($form_state['values']) ? $form_state['values']['filter'] : 1, 
  );
  $form['squadron_wrapper'] = array(
    '#type' => 'item',
    '#markup' => $table,
  );
  $form['#prefix'] = '<div id="squadron-mitesh">'; 
  $form['#suffix'] = '</div>';
  
  return $form ;
}

function _exercise_data_ajax_callback($form, $form_state){
  $form = drupal_rebuild_form($form['form_id']['#value'], $form_state, $old_form = NULL);
  return $form;
}

function searchForKey($search, $array_key, $array) {
  $keys = array();
   foreach ($array as $key => $val) {
    if(!empty($val[$array_key]) && ($val[$array_key] === $search)){
       $keys[] = $key;
    }
       
   }
   if(count($keys) >  1){
    return $keys; 
   }else{
    return null;
   }
}


function workoutSumData($array_key, $array) {
  
  $newArray = array(
    'nid' => '',
    'title' => '',
  );
  $total_calorie = 0;
  foreach($array_key as $key){
    $newArray['type'] = $array[$key]['type'];
    $newArray['date'] = $array[$key]['date'];
    $newArray['uri'] = $array[$key]['uri'];
    $total_calorie += (float)$array[$key]['total_calories'];
  }
  $newArray['total_calories'] = $total_calorie;
  
  return $newArray;
}

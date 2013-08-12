<?php
/**
 * callback function for user/member-home
 */
function runkeeper_user_member_home(){
  $output = render(drupal_get_form('runkeeper_user_autocomplete_form'));
  $output .= runkeeper_member_home();
  return $output; 
}


function runkeeper_user_today_activity(){
  
  
  $exerciseList = _personal_exercise_list();
  $value = '<div class="inner-grid-4">'.$exerciseList.'</div>
                      <div class="inner-grid-4">
                      	<h4>Exercise</h4>
                          <p><label>label :</label> ipsum, text here</p>
                          <p><label>label :</label> ipsum, text here</p>
                      </div>
                      <div class="inner-grid-4">
                      	<h4>Exercise</h4>
                          <p><label>label :</label> ipsum, text here</p>
                          <p><label>label :</label> ipsum, text here</p>
                          <p><label>label :</label> ipsum, text here</p>
                          <p><label>label :</label> ipsum, text here</p>
                      </div>';
  
  $fieldset['element'] = array(
    '#title' => t("Today's Activity"),
    '#children' => $value,
    '#collapsible' => true,
    '#collapsed' => false,
    '#attributes' => array('class' => array('collapsible', 'black-border'),),
  );
  
  return theme_fieldset($fieldset);
}


function _personal_exercise_list(){
  
  global $user;
  
  $from = time();
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'workout_entry')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_date', 'value', date('Y-m-d H:i:s',$from), '>')
    ->fieldOrderBy('field_date', 'value', 'DESC');
   
  $result = $query->execute();
  
  
  $plandata = array();
  if(!empty($result['node'])){
    foreach($result['node'] as $workoutid){
      $workout = node_load($workoutid->nid);
      $lang = $workout->language;
      $uid = runkeeper_plan_user($workout->field_plan[$lang][0]['nid']);
      $ClientName = runkeeper_user_profile_name($uid);
      $workout_type = !empty($workout->field_workout_type[$lang]) ? $workout->field_workout_type[$lang][0]['value'] : 'strength_training';
      $plandata[] = array(l($workout->title .' ('.$workout_type.')','node/'.$workout->nid));
    }  
  }
  
  return theme('item_list', array('items' => $plandata,'title' => t('Exercise'), 'type' => 'ul'));
  
}

function runkeeper_google_chart_filter_form($form, &$form_state){
 
  $form['form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter chart'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('black-border')),
  );
  
  $form['form']['progress'] = array(
    '#type' => 'select',
    '#title' => t('Show'),
    '#options' => array(
      'weight_loss' => t('Weight Loss'),
      'bfp' => t('Body Fat Percentage'),
      'chest_waist' => t('Chest to waist ratio'),
    ),
    '#ajax' => array(
        'wrapper' => 'google-chart-dashboard',
        'callback' => '_refresh_google_chart_data',
        'method' => 'replace',
     ),
  );
  
  $defaultVal = !empty($form_state['values']) ? $form_state['values']['filter'] : array('weight Training','Outdoor Activity','calorie intake');
   
  $form['form']['filter'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array(t('weight Training'),t('Outdoor Activity'),t('calorie intake'))),
    '#title' => t('with'),
    '#default_value' => $defaultVal, 
    '#ajax' => array(
        'wrapper' => 'google-chart-dashboard',
        'callback' => '_refresh_google_chart_data',
        'method' => 'replace',
     ),
  );
  
  $form['markup'] = array(
    '#markup' => draw_dashboard_chart(),     
  );
  
  $form['markup']['#prefix'] = '<div id="google-chart-dashboard">';
  $form['markup']['#suffix'] = '</div>'; 
  
  return $form;
  
}

function _refresh_google_chart_data($form, &$form_state){
    
    $filter = $form_state['values']['filter'];
    $filter['progress'] = $form_state['values']['progress'];
    //$filter['filter'] = $form_state['values']['filter'];
    
    $form['markup'] = array(
      '#markup' => draw_dashboard_chart($filter),     
    );  
  
    return $form['markup'];
}

function runkeeper_member_home(){
  $output = runkeeper_user_today_activity();
  $output .= render(drupal_get_form('runkeeper_google_chart_filter_form'));  
  return $output;
}

function draw_dashboard_chart($filter = array()){
  
  global $user;
  $header = array();
  
  $uid = (!empty($_SESSION['search_user']) && (arg(0) == 'user' || arg(0) == 'system')) ? $_SESSION['search_user'] : $user->uid;
  
  $pid = _runkeeper_user_plan_id($uid);
  $plan = node_load($pid);
  
  /*
  $start = !empty($plan->field_plan_date) ? $plan->field_plan_date[$plan->language][0]['value'] : "-1 month";
  $to = !empty($plan->field_plan_date) ? $plan->field_plan_date[$plan->language][0]['value2'] : "+1 Day";
  */
  
  $randnum = rand(1,100);
  
  $planData['pid'] = $pid; 
  $planData['start_date'] = $plan->field_plan_date[$plan->language][0]['value'];
  $planData['end_date'] = $plan->field_plan_date[$plan->language][0]['value2'];
  $planData['inital_weight'] = $plan->field_weight_initial[$plan->language][0]['value'];
  $planData['last_weight'] = $plan->field_weight_goal[$plan->language][0]['value'];
  $planData['inital_bfp'] = $plan->field_body_fat_initial[$plan->language][0]['value'];
  $planData['last_bfp'] = $plan->field_body_fat_goal[$plan->language][0]['value'];
  
  
  $rows   = getDashboardChartData($planData, $filter);
  $header = $columns = array('Date', 'Goal', 'Completed','tooltip');
  
  $settings = array();
  $settings['chart']['chartOne'.$randnum] = array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $columns,
    'fieldType' => array('date','number','number','tooltip'),
    'chartType' => 'Dashboard',
    'containerId' => 'dashboard_div',
    'ChartWrapper' => array(
        'chartType' => 'LineChart',
        'containerId' =>  'line_chart',
        'options' => array( // Optionals.
          'title' => 'Fitness Goal',
          'pointSize'=> 7,
          'width' => '100%',
          'height' => 400,
          'tooltip' => array('isHtml' => true, 'trigger'=> 'click'),
          'colors' => array('#ADAEB0','#5CB32E'),
          'legend' => array('position'=> 'top'),
          'lineWidth' => 3,
          'chartArea' =>array('width' => '90  %'),
          'hAxis' => array('gridlines' => array('color' => 'white')),      
        ),
    ),
    'ControlWrapper' => array( // Optionals.
      'controlType' => "ChartRangeFilter",
      'containerId' => 'filter_controll1',
      'options'=>array(
            'filterColumnLabel' => 'Date',
            'ui'=>array (
                  'chartType'=> 'LineChart',
                  'chartOptions'=> array(
                      'chartArea' => array('width' => 390,'height' => 100),
                      'hAxis' => array('baselineColor' => 'none'),
                      'colors' => array('#ADAEB0','#5CB32E'),
                     ),
                  //'snapToData' =>true,
                  'minRangeSize' => 5
             ),
            //'minRangeSize' => 86400000,
          )
    )
  );
  
  draw_chart($settings);
  return $output = '<div id="dashboard_div" style="height:600px;">
            <div id="line_chart"></div>
            <div id="filter_controll1" style="margin-left:0px;"></div>
          </div>';
          
}


function getDashboardChartData($planData, $filter){
  
  $from = strtotime($planData['start_date']);
  $to   = strtotime($planData['end_date']);
  $pid = $planData['pid'];
  
  
  if(!empty($filter['progress'])){
    $goal_type = $filter['progress'];
  }else{
    $goal_type = 'weight_loss';
  }
  
  switch($goal_type){
    case 'bfp':
      $goal_prefix = t('BFP');
    break;
    case 'chest_waist':
      $goal_prefix = t('Chest to Waist Ratio');
    break;
    default:
      $goal_prefix = t('Weight');
    break;
  }
  
  $strengthQuery = db_select('user_strength_activity','sa')
                      ->fields('sa',array('total_calories','uri','created','sid'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN');
  $strengthResult = $strengthQuery->execute()->fetchAll();
  
  
  
  $nutritionQuery = db_select('user_nutrition','sa')
                      ->fields('sa',array('total_calories','uri','created'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $nutritionResult = $nutritionQuery->fetchAll();
  
  
  $fitnessQuery = db_select('user_fitness_activity','sa')
                      ->fields('sa',array('total_calories', 'uri', 'created', 'type', 'total_distance'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $fitnessResult = $fitnessQuery->fetchAll();
  
  $measurementQuery = db_select('user_measurements','um')
                      ->fields('um',array('id', 'created', 'type', 'weight'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $measurementResult = $measurementQuery->fetchAll();
  
  $row = array();
  
  $container_div = '<div style="padding: 10px; max-width: 200px">';
  $clr_fit_activity= 'font-weight:bold; color: #207CCA;';
  $clr_str_training= 'font-weight:bold; color: #23D32F;';
  $clr_cal_intake= 'font-weight:bold; color: #EF9628;';
  
  $goalData = getGoalData($from, $planData, $goal_type);
  $row[] = array($from, (int)$goalData,(int)$goalData,"");  
  
  $randnum = 0;
  if(empty($filter)){
    foreach($strengthResult as $strengthRecord){
      $WeightData = getWeightLossData($strengthRecord->created, $goal_type, $planData['pid']);
      $goalData = getGoalData($strengthRecord->created ,$planData , $goal_type);
      $strengthTitle = get_strength_activity_title($strengthRecord->sid);
      //$chest_waist = $WeightData->chest_waist;  
      
      if(!empty($WeightData->{$goal_type}))
         $row[] = array($WeightData->created, (float)$goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_str_training'>Strength:</h5><p>{$strengthTitle}, {$strengthRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p></div>");//$container_div .
         
    }
    
    foreach($nutritionResult as $nutritionRecord){
      
      $WeightData = getWeightLossData($nutritionRecord->created, $goal_type, $planData['pid']);
      $goalData = getGoalData($nutritionRecord->created ,$planData, $goal_type);
      
      if(!empty($WeightData->{$goal_type}))
        $row[] = array($nutritionRecord->created, (float)$goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_cal_intake'>Nutrition:</h5><p>consumed {$nutritionRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p>");
        
    }
    
    foreach($fitnessResult as $fitnessRecord){
      $goalData = getGoalData($fitnessRecord->created ,$planData , $goal_type);
      $WeightData = getWeightLossData($fitnessRecord->created, $goal_type, $planData['pid']);
      $title = $fitnessRecord->type .', '.$fitnessRecord->total_distance.' distance';
      
      if(!empty($WeightData->{$goal_type}))
        $row[] = array($fitnessRecord->created, $goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_fit_activity'>Outdoor: </h5><p>{$title}, {$fitnessRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p></div>");
    }
    
    
    foreach($measurementResult as $measurementRecord) {
      $goalData = getGoalData($measurementRecord->created ,$planData , $goal_type);
      $WeightData = getWeightLossData($measurementRecord->created, $goal_type, $planData['pid']);
      $title = $measurementRecord->type .'- '.$measurementRecord->weight;
      
      if(!empty($WeightData->{$goal_type}))
        $row[] = array($measurementRecord->created, $goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_fit_activity'>Outdoor: </h5><p>{$title} {$goal_prefix}</p></div>");
    }
    
    
  }else{
    if($filter['weight Training']){
      foreach($strengthResult as $strengthRecord){
        $WeightData = getWeightLossData($strengthRecord->created, $goal_type, $planData['pid']);
        $goalData = getGoalData($strengthRecord->created ,$planData , $goal_type);
        $strengthTitle = get_strength_activity_title($strengthRecord->sid);
        //$chest_waist = $WeightData->chest_waist;  
        
        if(!empty($WeightData->{$goal_type}))
           $row[] = array($WeightData->created, (float)$goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_str_training'>Strength:</h5><p>{$strengthTitle}, {$strengthRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p></div>");//$container_div .
           
      }
    } 
    
    if($filter['calorie intake']){
      foreach($nutritionResult as $nutritionRecord){
          $WeightData = getWeightLossData($nutritionRecord->created, $goal_type, $planData['pid']);
          $goalData = getGoalData($nutritionRecord->created ,$planData, $goal_type);
          
          if(!empty($WeightData->{$goal_type}))
            $row[] = array($nutritionRecord->created, (float)$goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_cal_intake'>Nutrition:</h5><p>consumed {$nutritionRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p>");
            
        }
    }
    
    if($filter['Outdoor Activity']){
      foreach($fitnessResult as $fitnessRecord){
        $goalData = getGoalData($fitnessRecord->created ,$planData , $goal_type);
        $WeightData = getWeightLossData($fitnessRecord->created, $goal_type, $planData['pid']);
        $title = $fitnessRecord->type .', '.$fitnessRecord->total_distance.' distance';
        
        if(!empty($WeightData->{$goal_type}))
          $row[] = array($fitnessRecord->created, $goalData, $WeightData->{$goal_type}, $container_div . "<h5 style='$clr_fit_activity'>Outdoor: </h5><p>{$title}, {$fitnessRecord->total_calories} calories, ".$WeightData->{$goal_type}." {$goal_prefix}</p></div>");
      } 
    }
    
  }
  
  $goalData = getGoalData($to, $planData, $goal_type);
  $row[] = array($to, (int)$goalData, null,"");
  
  usort($row, "sortDate");
  
  $i = 0;
  $records = array();
  
  foreach($row as $record){
    $date = date('Y,m,d', $record[0]);
    $records[] = array($date, $record[1], $record[2], $record[3]);
    $i++;  
  }
  
  return $records;
  
}

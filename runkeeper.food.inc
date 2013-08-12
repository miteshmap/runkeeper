<?php

function runkeeper_user_food_page(){
  $output = render(drupal_get_form('runkeeper_user_autocomplete_form'));
  $output .= runkeeper_food_page();
  return $output;
}

function runkeeper_food_page(){
  global $user;
  
  $uid = (!empty($_SESSION['search_user']) && arg(0) == 'user') ? $_SESSION['search_user'] : $user->uid;
  $pid = _runkeeper_user_plan_id($user->uid);
  
  $rows = array();
  $records = array();
  $output = render(drupal_get_form('runkeeper_food_data_table',$uid));
  $output .= views_embed_view('recipe','block');
  /*
  for($i=0;$i<3;$i++){
    
  $output .= '<div class="inner-grid-4">
                  <div class="box box-main pad-small">
                      <div class="content">
                          <div class="wrap-small">
                              <h3>Recipe title</h3>
                          </div>
                          <div class="wrap-small">
                              <img alt="" src="http://placehold.it/170x100">
                          </div>
            
                          <div class="wrap-small">
                              Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
                              tempor incididunt ut labore et dolore magna aliqua.
                          </div>
            
                          <div class="wrap-small">
                              <a class="btn btn-main expanded" href="#">View Recipe</a>
                          </div>
                      </div>
                  </div>
              </div>';
  
  }
  */
  
  $from = strtotime('-1 month');
  $to   = time();
  $strengthQuery = db_select('user_strength_activity','sa')
                      ->fields('sa',array('total_calories','uri','created'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $strengthResult = $strengthQuery->fetchAll();
  
  $row = array();
  foreach($strengthResult as $strengthRecord){
    $row[] = array($strengthRecord->created, rand(3,40),(int)$strengthRecord->total_calories, "<h3>Strength training</h3><p>completed {$strengthRecord->total_calories}</p>");
  }
  
  if($row){
    usort($row, "sortDate");
    $i = 0;
    foreach($row as $record){
      $date = date('Y,m,d', $record[0]);
      $records[] = array($date, $i*20, $record[2], $record[3]);
      $i++;  
    }  
  }
  
  
  $rows = $records;
  $header = $columns = array('Date', 'Goal', 'Completed','tooltip');
  
   $settings = array();
   $settings['chart']['chartOne'] = array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $columns,
    'fieldType' => array('date','number','number','tooltip'),
    'chartType' => 'LineChart',
    'containerId' =>  'line_chart',
    'options' => array( // Optionals.
      'curveType' => "function",
      'forceIFrame' => FALSE,
      'title' => 'Strength',
      'width' => 200,
      'height' => 150,
      'tooltip' => array('isHtml' => true, 'trigger'=> 'click'),
      'colors' => array('#ADAEB0','#5CB32E'),
    ),
  );
  
  $nutritionQuery = db_select('user_nutrition','sa')
                      ->fields('sa',array('total_calories','uri','created'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $nutritionResult = $nutritionQuery->fetchAll();
  
  foreach($strengthResult as $strengthRecord){
    $row[] = array($strengthRecord->created, rand(3,40),(int)$strengthRecord->total_calories, "<h3>Strength training</h3><p>completed {$strengthRecord->total_calories}</p>");
  }
  
  usort($row, "sortDate");
  $i = 0;
  foreach($row as $record){
    $date = date('Y,m,d', $record[0]);
    $records[] = array($date, $i*20, $record[2], $record[3]);
    $i++;  
  }
  
  $rows = $records;
  
  
  
  $settings['chart']['chartTwo'] = array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $columns,
    'fieldType' => array('date','number','number','tooltip'),
    'chartType' => 'LineChart',
    'containerId' =>  'line_chart2',
    'options' => array( // Optionals.
      'curveType' => "function",
      'forceIFrame' => FALSE,
      'title' => 'Nutrition',
      'width' => 200,
      'height' => 150,
      'tooltip' => array('isHtml' => true, 'trigger'=> 'click'),
      'colors' => array('#ADAEB0','#5CB32E'),
    ),
  );
  
  
  
  $fitnessQuery = db_select('user_fitness_activity','sa')
                      ->fields('sa',array('total_calories','uri','created'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      ->execute();
  $fitnessResult = $fitnessQuery->fetchAll();
  
  
  foreach($strengthResult as $strengthRecord){
    $row[] = array($strengthRecord->created, rand(3,40),(int)$strengthRecord->total_calories, "<h3>Strength training</h3><p>completed {$strengthRecord->total_calories}</p>");
  }
  
  usort($row, "sortDate");
  $i = 0;
  foreach($row as $record){
    $date = date('Y,m,d', $record[0]);
    $records[] = array($date, $i*20, $record[2], $record[3]);
    $i++;  
  }
  
  $rows = $records;
  
  $settings['chart']['chartThree'] = array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $columns,
    'fieldType' => array('date','number','number','tooltip'),
    'chartType' => 'LineChart',
    'containerId' =>  'line_chart3',
    'options' => array( // Optionals.
      'curveType' => "function",
      'forceIFrame' => FALSE,
      'title' => 'Fitness',
      'width' => 200,
      'height' => 150,
      'tooltip' => array('isHtml' => true, 'trigger'=> 'click'),
      'colors' => array('#ADAEB0','#5CB32E'),
    ),
  );
  
  draw_chart($settings);
  $output .= '<ul class="food_chart">
                <li><div id="line_chart"></div></li>
                <li><div id="line_chart2"></div></li>
                <li><div id="line_chart3"></div></li>
              </ul>';
  
  return $output;
  
}


function runkeeper_get_recipe_titles($record){
  $title = array();
  if(!empty($record)){
    $calorie = 0;
    foreach($record as $data){
      $node = node_load($data['nid']);
      $lang = $node->language;  
      $title[] = $node->title;
      $calorie += (float)$node->field_recipe_calorie[$lang][0]['value'];
    }
  }
  return array('title' => join(',',$title),'calorie' => $calorie);
}


function runkeeper_food_data_table($form, &$form_state, $uid){
  //global $user;
  if(!empty($form_state['values'])){
    $week = $form_state['values']['filter'];
    $week = "-$week Week";
  }else{
    $week = '-1 Week';
  }
  
  $from = strtotime($week);
  $to   = time();
  
  $pid = _runkeeper_user_plan_id($uid);
  
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'recipe_relation')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_date', 'value', array(date('Y-m-d H:i:s',$from), date('Y-m-d H:i:s',$to)), 'BETWEEN')
    ->fieldCondition('field_plan','nid', $pid);
    
  $result = $query->execute();
  
  $food = array();
  if(!empty($result['node'])){
    foreach($result['node'] as $planid){
      $recipe = node_load($planid->nid);
      $lang = $recipe->language;
      $recipesData = runkeeper_get_recipe_titles($recipe->field_recipe_entry[$lang]);
      $food[] = array(
        'nid' =>  $recipe->nid,
        'date' => date('d-m-Y',strtotime($recipe->field_date[$lang][0]['value'])),
        'type' => $recipe->field_meal[$lang][0]['value'],
        'title' =>  limit_words($recipesData['title'],5),
        'calorie' =>  $recipesData['calorie'],
      );
    }  
  }
  
  
  $row = array();
  foreach($food as $record){
    $url = !empty($record['nid']) ? 'node/'.$record['nid'] : '#';
    $calories = !empty($record['calorie']) ? $record['calorie'] : t('Missing');
    $row[] = array($record['date'],$calories,$record['title'],l('view details',$url,array('attributes' => array('target' => '_blank'))));
  }
  
  $data = $row;
  
  $headers = array(t('Date'), t('Total Calories'), t('Name'),t(''));
  
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
      '1' => t('Last week 1'),
      '2' => t('Last week 2'),
      '3' => t('Last week 3'),
      '4' => t('Last week 4'),
    ),
    '#ajax' => array(
        'event' => 'change',
        'wrapper' => 'food-history',
        'callback' => '_food_data_ajax_callback',
        'method' => 'replace',
     ),
    '#default_value' => !empty($form_state['values']) ? $form_state['values']['filter'] : 1, 
  );
  $form['squadron_wrapper'] = array(
    '#type' => 'item',
    '#markup' => $table,
  );
  $form['#prefix'] = '<div id="food-history">'; 
  $form['#suffix'] = '</div>';
  
  return $form ;
}

function _food_data_ajax_callback($form, $form_state){
  $form = drupal_rebuild_form($form['form_id']['#value'], $form_state, $old_form = NULL);
  return $form;
}

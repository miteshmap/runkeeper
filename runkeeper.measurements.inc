<?php

module_load_include('inc', 'runkeeper', 'runkeeper.dashboard');

function runkeeper_user_measurements_page(){
  $output = render(drupal_get_form('runkeeper_user_autocomplete_form'));
  $output .= runkeeper_measurements_page();
  return $output;
}


function runkeeper_measurements_page(){
  global $user;
  $uid = (!empty($_SESSION['search_user']) && arg(0) == 'user') ? $_SESSION['search_user'] : $user->uid;
  $output = render(drupal_get_form('runkeeper_measurement_chart_form',$uid));
  return $output;
}

function runkeeper_measurement_chart_form($form, &$form_state, $uid){
  
  $form['date_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter By Date'),
    '#collapsible' => true,
    '#collapsed' => false,
    '#attributes' => array('class' => array('black-border')),
  );
  
  $form['date_filter']['date_start'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-3:+3',
    '#datepicker_options' => array('minDate' => '-3m'),
    '#default_value' => format_date(strtotime('-1 month'),'custom','Y-m-d'),
  );
  
  $form['date_filter']['date_end'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-3:+3',
    '#datepicker_options' => array('maxDate' => 0),
    '#default_value' => format_date(time(),'custom','Y-m-d'),  
  );
  
  $form['date_filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('search'),
    '#ajax' => array(
        'wrapper' => 'google-chart-measurements',
        'callback' => '_ajax_runkeeper_measurement_chart_form',
        'method' => 'replace',
    )
  );
  
  //watchdog('dates','start-date--'.$form_state['values']['date_start']);
  /*
  if(!empty($form_state['values']['date_start']) || !empty($form_state['values']['date_end'])){
    $form['markup'] = array(
      '#markup' => runkeeper_measurements_chart_page($uid, $form_state['values']['date_start'], $form_state['values']['date_end']),
    );
  }
  else{
    */
    $form['markup'] = array(
      '#markup' => runkeeper_measurements_chart_page($uid),
    );  
  //}
  
  $form['markup']['#prefix'] = '<div id="google-chart-measurements">';
  $form['markup']['#suffix'] = '</div>';
  
  return $form;
}

function _ajax_runkeeper_measurement_chart_form($form, &$form_state){
  //$form = drupal_rebuild_form($form['form_id']['#value'], $form_state, $old_form = NULL);
  $form['markup'] = array(
      '#markup' => runkeeper_measurements_chart_page($uid, $form_state['values']['date_start'], $form_state['values']['date_end']),
  );
  
  return $form['markup'];
}

function runkeeper_measurements_chart_page($uid, $start_date = NULL, $end_date = NULL){
  
  $pid = _runkeeper_user_plan_id($uid);
  $header = array();
  $randnum=rand(1,100);
  $from =  !empty($start_date) ? strtotime($start_date) : strtotime('-1 month');
  $to   = !empty($end_date) ? strtotime($end_date) : time();  
  $record = 3;
  
  
  $chartDiv = '';
  $settings = array();
  
  $measurementQuery = db_select('user_measurements','um')
                      ->fields('um',array('weight','waist','chest','bicep','thigh','calf','forearm','blood_pressure','blood_fat_percentage','created'))
                      ->condition('pid',$pid)
                      ->condition('created', array($from, $to), 'BETWEEN')
                      //->condition('um.type', array('final', 'initial', 'goal'), 'NOT IN')
                      ->execute();
  $measurementResult = $measurementQuery->fetchAll();

  $weightrecord = getMeasurementData($measurementResult, 'weight');
  $headers = array(t('Date'), t('Weight'));
  if(count($weightrecord) <= $record){
    $weightTable = getMeasurementDataTable($headers,$weightrecord);
  } else{
    $weightTable = '';
    $settings['chart']['weight'.$randnum] = measurement_chart_settings('weight', $headers, $weightrecord, t('weight')); 
  }
  
  
  $waistrecord = getMeasurementData($measurementResult, 'waist');
  $headers = array(t('Date'), t('Waist'));
  if(count($waistrecord) <= $record){
    $waistTable = getMeasurementDataTable($headers,$waistrecord);      
  } else{
    $waistTable = '';
    $settings['chart']['waist'.$randnum] = measurement_chart_settings('waist', $headers, $waistrecord, t('Waist')); 
  }
  
  
  $chestrecord = getMeasurementData($measurementResult, 'chest');
  $headers = array(t('Date'), t('Chest'));
  if(count($chestrecord) <= $record){
    $chestTable = getMeasurementDataTable($headers,$waistrecord);
  } else{
    $chestTable = '';
    $settings['chart']['chest'.$randnum] = measurement_chart_settings('chest', $headers, $chestrecord, t('Chest')); 
  }
  
  $biceprecord = getMeasurementData($measurementResult, 'bicep');
  $headers = array(t('Date'), t('Bicep'));
  if(count($biceprecord) <= $record){
    $bicepTable = getMeasurementDataTable($headers,$biceprecord);
  } else{
    $bicepTable = '';
    $settings['chart']['bicep'.$randnum] = measurement_chart_settings('bicep', $headers, $biceprecord, t('Bicep')); 
  }

  
  $thighrecord = getMeasurementData($measurementResult, 'thigh');
  $headers = array(t('Date'), t('Thigh'));
  if(count($thighrecord) <= $record){
    $thighTable = getMeasurementDataTable($headers,$thighrecord);
  } else{
    $thighTable = '';
    $settings['chart']['thigh'.$randnum] = measurement_chart_settings('thigh', $headers, $thighrecord, t('Thigh')); 
  }
  
  
  $calfrecord = getMeasurementData($measurementResult, 'calf');
  $headers = array(t('Date'), t('Calves'));
  if(count($calfrecord) <= $record){
    $calfTable = getMeasurementDataTable($headers,$calfrecord);
  } else{
    $calfTable = '';
    $settings['chart']['calves'.$randnum] = measurement_chart_settings('calves', $headers, $calfrecord, t('Calves')); 
  }
  
  $forearmrecord = getMeasurementData($measurementResult, 'forearm');
  $headers = array(t('Date'), t('Forearm'));
  
  if(count($forearmrecord) <= $record){
    $forearmTable = getMeasurementDataTable($headers,$forearmrecord);       
  } else{
    $forearmTable = '';
    $settings['chart']['forearm'.$randnum] = measurement_chart_settings('forearm', $headers, $forearmrecord, t('ForeArm')); 
  }
  
  
  $blood_pressure_record = getMeasurementData($measurementResult, 'blood_pressure');
  $headers = array(t('Date'), t('Pressure'));
  
  if(count($blood_pressure_record) <= $record){
    $bloodPressureTable = getMeasurementDataTable($headers,$blood_pressure_record);      
  } else{
    $bloodPressureTable = '';
    $settings['chart']['blood_pressure'.$randnum] = measurement_chart_settings('blood_pressure', $headers, $blood_pressure_record, t('Blood Pressure'));
  }
  
  
  $blood_fat_percentage_record = getMeasurementData($measurementResult, 'blood_fat_percentage');
  $headers = array(t('Date'), t('BFP'));
  if(count($blood_fat_percentage_record) <= $record){
    $bfpTable = getMeasurementDataTable($headers,$blood_fat_percentage_record);
  } else{
    $bfpTable = ''; 
    $settings['chart']['blood_fat_per'.$randnum] = measurement_chart_settings('blood_fat_per', $headers, $blood_fat_percentage_record, t('Blood Fat Percentage'));
  }
  
  $chartDiv = '<li><div id="line_chart_weight">'.$weightTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_waist">'.$waistTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_chest">'.$chestTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_bicep">'.$bicepTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_thigh">'.$thighTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_forearm">'.$forearmTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_blood_pressure">'.$bloodPressureTable.'</div></li>';
  $chartDiv .= '<li><div id="line_chart_blood_fat_per">'.$bfpTable.'</div></li>';
  
  if(!empty($settings))
    draw_chart($settings);
  $output = '<ul class="measurement_chart_group">'.$chartDiv.'</ul>';
  return $output;
}


function measurement_chart_settings($type, $header, $rows, $title){
  return array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $header,
    'fieldType' => array('date','number'),
    'chartType' => 'LineChart',
    'containerId' =>  'line_chart_'.$type,
    'options' => array( // Optionals.
      'curveType' => "function",
      'forceIFrame' => FALSE,
      'title' => $title,
      'pointSize'=> 5,
      'width' => 200,
      'height' => 150,
      'tooltip' => array('isHtml' => true, 'trigger'=> 'click'),
      'colors' => array('#5CB32E'),
      'chartArea' =>array('width' => '99%'),
    ),
  );
}

function getMeasurementDataTable($header, $data){
  
  $newdata = array();
  foreach($data as $row){
    $row[0] = date('F d, Y',strtotime(str_replace(',','-',$row[0])));
    $newdata[] = $row; 
  }
  
  
  return theme('table', array(
            'header' => $header, 
            'rows' => $newdata, 
            'empty' => t('No items found.'),
            'attributes' => array('class' => array('data-table'))
          )); 
}


function getMeasurementData($measurementResult, $field){
  
  $data = array();
  foreach($measurementResult as $measurementRecord){
    $data[] = array($measurementRecord->created, (int)$measurementRecord->{$field});
  }
  
  usort($data, "sortDate");
  
  $i = 0;
  $dataRecord = array();
  foreach($data as $record){
    $date = date('Y,m,d', $record[0]);
    $dataRecord[] = array($date, $record[1]);
    $i++;  
  }
  
  return $dataRecord;
  
}

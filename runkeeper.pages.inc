<?php

function runkeeper_show_fitness_activities($account) {
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  $data = runkeeper_client_request('FitnessActivityFeed', 'Read');
  
  //$data = runkeeper_perform_request('/fitnessActivities', 'GET', 'application/vnd.com.runkeeper.FitnessActivityFeed+json', NULL);
  $headers = array(t('has_map'), t('Duration'), t('Total Distance'), t('Entry Mode'), t('Source'), t('Start Time'), t('Type'), t('URI'));
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/fitness-activities'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));
}

function runkeeper_get_fitness_activity_details($account, $activity_type, $id) {
  if ($activity_type && $id) {
    //$data = runkeeper_perform_request('/' . $activity_type . '/' . $id, 'GET', 'application/vnd.com.runkeeper.FitnessActivity+json');
    $data = runkeeper_client_request('FitnessActivity','Read', null, '/' . $activity_type . '/' . $id);
    kpr($data);
    return '';
  }
}

function runkeeper_show_weight_feed($account) {
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  $data = runkeeper_client_request('WeightFeed', 'Read');
  //$data = runkeeper_perform_request('/weight', 'GET', 'application/vnd.com.runkeeper.WeightFeed+json', NULL);
  $headers = array(t('Timestamp'), t('Weight'), t('URI'),);
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/weight-feed'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));
}

function runkeeper_show_weight_details($account, $weight, $id) {
  if ($weight && $id) {
    $data = runkeeper_client_request('WeightFeed', 'Read', null, '/' . $weight . '/' . $id);
    //$data = runkeeper_perform_request('/' . $weight . '/' . $id, 'GET', 'application/vnd.com.runkeeper.Weight+json');
    kpr($data);
    return '';
  }
}

function runkeeper_show_strength_training_feed($account) {
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  $data = runkeeper_client_request('StrengthTrainingActivityFeed', 'Read');
  //$data = runkeeper_perform_request('/strengthTrainingActivities', 'GET', 'application/vnd.com.runkeeper.StrengthTrainingActivityFeed+json', NULL);
  $headers = array(t('Start Time'), t('URI'));
  //kpr($data);
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/strength-training'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));
}


function runkeeper_show_strength_activity_details($account, $strength, $id) {
  if ($strength && $id) {
    //$data = runkeeper_perform_request('/' . $strength . '/' . $id, 'GET', 'application/vnd.com.runkeeper.StrengthTrainingActivity+json');
    $data = runkeeper_client_request('StrengthTrainingActivity', 'Read', null, '/' . $strength . '/' . $id);
    kpr($data);
    return '';
  }
}

function  runkeeper_show_nutrition_measurements($account) {
  
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  //$data = runkeeper_perform_request('/nutrition', 'GET', 'application/vnd.com.runkeeper.NutritionSetFeed+json', NULL);
  $data = runkeeper_client_request('NutritionSetFeed', 'Read');
  
  $headers = array(t('Timestamp'), t('Protein'), t('Fat'), t('Calories'), t('Carbohydrates'), t('Sodium'), t('Fiber'), t('URI'), t('Meal'));
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/nutrition'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));
}


function runkeeper_show_nutrition_activity_details($account, $nutrition, $id) {
  if ($nutrition && $id) {
    //$data = runkeeper_perform_request('/' . $nutrition . '/' . $id, 'GET', 'application/vnd.com.runkeeper.NutritionSet+json');
    $data = runkeeper_client_request('NutritionSet', 'Read', null, '/' . $nutrition . '/' . $id);
    kpr($data);
    return '';
  }
}


function runkeeper_show_background_activities($account) {
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  //$data = runkeeper_perform_request('/backgroundActivities', 'GET', 'application/vnd.com.runkeeper.BackgroundActivityFeed+json', NULL);
  $data = runkeeper_client_request('BackgroundActivityFeed', 'Read');
  $headers = array(t('Timestamp'), t('Calories Burned'), t('Steps'), t('URI'));
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/background-activities'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));  
}

function runkeeper_show_background_activity_details($account, $background, $id) {
  if ($background && $id) {
    //$data = runkeeper_perform_request('/' . $background . '/' . $id, 'GET', 'application/vnd.com.runkeeper.BackgroundActivity+json');
    $data = runkeeper_client_request('BackgroundActivity', 'Read', null, '/' . $background . '/' . $id);
    kpr($data);
    return '';
  }
}

function runkeeper_show_general_measurements($account) {
  //$now = date('Y-m-d');
  //$one_month_ago = date('Y-m-d',strtotime( '-1 month'));
  //$optionparam = array('noEarlierThan' => $one_month_ago, 'noLaterThan' => $now);
  //$data = runkeeper_perform_request('/generalMeasurements', 'GET', 'application/vnd.com.runkeeper.GeneralMeasurementSetFeed+json', NULL);
  $data = runkeeper_client_request('GeneralMeasurementFeed', 'Read');
  $headers = array(t('Timestamp'), t('Vitamin D'), t('HSCRP'), t('CRP'), t(''), t('TSH'), t('Uric Acid'), t('Systolic'), t('Diastolic'), t('Resting Heartrate'), t('Total Cholesterol'), t('HDL'), t('LDL'), t('URI'));
  //kpr($data);
  foreach($data['items'] as $k => $item) {
    $data['items'][$k]['uri'] = l($item['uri'], 'user/' . $account->uid . '/general-measurements'  . $item['uri']);
  }
  return theme('table', array('header' => $headers, 'rows' => $data['items'], 'empty' => t('No items found.'),'attributes' => array('class' => array('data-table'))));  
}

function runkeeper_show_general_measurement_details($account, $general_measurement, $id) {
  if ($background && $id) {
    //$data = runkeeper_perform_request('/' . $general_measurement . '/' . $id, 'GET', 'application/vnd.com.runkeeper.BackgroundActivity+json');
    $data = runkeeper_client_request('GeneralMeasurement', 'Read', null, '/' . $general_measurement . '/' . $id);
    kpr($data);
    return '';
  }
}
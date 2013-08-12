<?php

/**
 * Implements hook_menu().
 */
function runkeeper_admin_settings() {
  
  $form = array();
  
  $form['runkeeper_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Base url'),
    '#default_value' => variable_get('runkeeper_base_url', 'https://api.runkeeper.com'),
    '#required' => TRUE,
  );

  $form['runkeeper_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Client ID'),
    '#default_value' => variable_get('runkeeper_client_id', 'b0bac7bd422046aa8cdd1c28bf9201e9'),
    '#required' => TRUE,
  );
  
  $form['runkeeper_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Secret key'),
    '#default_value' => variable_get('runkeeper_secret_key', '5c911bcc7708460ca4fdac4e58d38eb4'),
    '#required' => TRUE,
  );
  
  $form['runkeeper_authorize_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Authorize url'),
    '#default_value' => variable_get('runkeeper_authorize_url', 'https://runkeeper.com/apps/authorize'),
    '#required' => TRUE,
  );
  
  $form['runkeeper_token_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper token url'),
    '#default_value' => variable_get('runkeeper_token_url', 'https://runkeeper.com/apps/token'),
    '#required' => TRUE,
  );
  
  $form['runkeeper_deauthorize_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Deauthorize url'),
    '#default_value' => variable_get('runkeeper_deauthorize_url', 'https://runkeeper.com/apps/de-authorize'),
    '#required' => TRUE,
  );
  
  $form['runkeeper_token_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Runkeeper Token Type'),
    '#default_value' => variable_get('runkeeper_token_type', 'Bearer'),
    '#required' => TRUE,
  );
  
  return system_settings_form($form);
}

function runkeeper_admin_test(){
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Runkeeper Test',
  ); 
  return $form;
}

function runkeeper_admin_test_submit($form, &$form_state){
  
  //$fields = json_decode('{"type": "Running", "equipment": "None", "start_time": "Tue, 16 Apr 2013 00:00:00", "notes": "My first late-night run", "path": [{"timestamp":0, "altitude":0, "longitude":-70.95182336425782, "latitude":42.312620297384676, "type":"start"}, {"timestamp":8, "altitude":0, "longitude":-70.95255292510987, "latitude":42.31230294498018, "type":"end"}], "post_to_facebook": true, "post_to_twitter": true}');
  //$rkCreateActivity = runkeeper_client_request('NewFitnessActivity','Create',$fields);
  //$fields = json_decode('{"notes": "My first Long day run"}');
  //$rkUpdateActivity = runkeeper_client_request('FitnessActivityUpdate','Update',$fields,'/fitnessActivities/151319736');
  
  $rkProfile = runkeeper_client_request('Profile','Read');
  
	if ($rkProfile) {
    drupal_set_message(t('Your configuration is Perfect'));
		drupal_set_message(t('Name: @name',array('@name' => $rkProfile['name'])));
    drupal_set_message(t('Athlete Type: @athlete_type',array('@athlete_type' => $rkProfile['athlete_type'])));
    drupal_set_message(t('Profile: @profile',array('@profile' => $rkProfile['profile'])));
	}
	else {
		drupal_set_message(t('Error: @error',array('@error' => $rkAPI->api_last_error)));
	}
}
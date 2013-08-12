<?php

/**
 * callback function for admin/dashboard
 */
function runkeeper_admin_dashboard(){
  
  drupal_set_title('Upcoming Workouts');
  $output = customer_exercise_list();
  $output .= trainer_customer_list();
  $output .= admin_general_link_list();
  
  return $output; 
}



function customer_exercise_list(){
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
      $trainerId = $workout->field_instructor[$lang][0]['uid'];
      $Trainer = runkeeper_user_profile_name($trainerId);
      $plandata[] = array(
        l($ClientName,'user/'.$uid),
        $workout->title .' ('.$workout_type.')',
        format_date(strtotime($workout->field_date[$lang][0]['value']),'custom','h:i:s'),
        l($Trainer,'user/'.$trainerId),
      );
    }  
  }
  
  $header = array('Customer','Exercise', 'Time', 'Trainer');
  
  return theme('table', array(
                  'header' => $header,
                  'rows' => $plandata,
                  'empty' => t('No items found.'),
                  'attributes' => array('class' => array('data-table'))
                ));
  
}

function trainer_customer_list(){
  
  $role = user_role_load_by_name('Customer');
  $result = db_select('users_roles', 'ur')
        ->fields('ur', array('uid'))
        ->condition('rid', $role->rid)
        ->execute()
        ->fetchAll();
  
  $uids = array();
  foreach($result as $record) {
    $username = runkeeper_user_profile_name($record->uid);
    $uids[] = array(l($username,'user/'.$record->uid));
  }
  
  $header = array('Customer');
  return theme('table', array(
                  'header' => $header,
                  'rows' => $uids,
                  'empty' => t('No items found.'),
                  'attributes' => array('class' => array('data-table'),'style' => 'width:30%;float:left;')
                ));
}

function admin_general_link_list(){
  
  $header = array('Pages','Add','List');
  $rows = array(
    array(t('User'), l(t('Add'),'admin/people/create'), l(t('List'),'admin/people')),
    array(t('Plan'), l(t('Add'),'node/add/plan'), l(t('List'),'admin/content',array('query' => array('type'=>'plan')))),
    array(t('Measurements'), l(t('Add'),'node/add/measurements'), l(t('List'),'admin/content/measurements')),
    array(t('Workout'), l(t('Add'),'node/add/workout-entry'), l(t('List'),'admin/content',array('query' => array('type'=>'workout_entry')))),
    array(t('Recipe'), l(t('Add'),'node/add/recipe-relation'), l(t('List'),'admin/content',array('query' => array('type'=>'recipe_relation')))),
    array(t('Recipe Entry'), l(t('Add'),'node/add/recipe-entry'), l(t('List'),'admin/content',array('query' => array('type'=>'recipe_entry')))),
    
  );
  
  return theme('table', array(
                  'header' => $header,
                  'rows' => $rows,
                  'empty' => t('No items found.'),
                  'attributes' => array('class' => array('data-table'),'style' => 'width:65%;float:right;')
                ));
}
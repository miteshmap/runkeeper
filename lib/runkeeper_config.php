<?php
global $runKeeperConfig;
$runKeeperConfig = new stdClass(); 
$runKeeperConfig->App = new stdClass();
$runKeeperConfig->App->client_id = variable_get('runkeeper_client_id', 'b0bac7bd422046aa8cdd1c28bf9201e9');
$runKeeperConfig->App->client_secret = variable_get('runkeeper_secret_key', '5c911bcc7708460ca4fdac4e58d38eb4');
$runKeeperConfig->App->auth_url = variable_get('runkeeper_authorize_url', 'https://runkeeper.com/apps/authorize');
$runKeeperConfig->App->access_token_url = variable_get('runkeeper_token_url', 'https://runkeeper.com/apps/token');
$runKeeperConfig->App->redirect_uri = url(current_path(), array('absolute' => TRUE));
$runKeeperConfig->App->api_base_url = variable_get('runkeeper_base_url', 'https://api.runkeeper.com');
$runKeeperConfig->App->new_url = 'https://api.runkeeper.com';

/**
 * Interface parameter 
 * If you want perfect results.You won't Need to change anything below this
 */

$runKeeperConfig->Interfaces = new stdClass();
$runKeeperConfig->Interfaces->User = new stdClass();
$runKeeperConfig->Interfaces->User->Name = 'User';
$runKeeperConfig->Interfaces->User->Media_Type = 'application/vnd.com.runkeeper.User+json';
$runKeeperConfig->Interfaces->User->Read = new stdClass();
$runKeeperConfig->Interfaces->User->Read->Method = 'GET';
$runKeeperConfig->Interfaces->User->Read->Url = '/user';
 
$runKeeperConfig->Interfaces->Profile = new stdClass();
$runKeeperConfig->Interfaces->Profile->Name = 'Profile';
$runKeeperConfig->Interfaces->Profile->Media_Type = 'application/vnd.com.runkeeper.Profile+json';
$runKeeperConfig->Interfaces->Profile->Read = new stdClass();
$runKeeperConfig->Interfaces->Profile->Read->Method = 'GET';
$runKeeperConfig->Interfaces->Profile->Read->Url = '/profile';

$runKeeperConfig->Interfaces->Settings = new stdClass();
$runKeeperConfig->Interfaces->Settings->Name = 'Settings';
$runKeeperConfig->Interfaces->Settings->Media_Type = 'application/vnd.com.runkeeper.Settings+json';
$runKeeperConfig->Interfaces->Settings->Read = new stdClass();
$runKeeperConfig->Interfaces->Settings->Read->Method = 'GET';
$runKeeperConfig->Interfaces->Settings->Read->Url = '/settings';


/**
 * fitness activity feed
 */
$runKeeperConfig->Interfaces->FitnessActivityFeed = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivityFeed->Name = 'FitnessActivityFeed';
$runKeeperConfig->Interfaces->FitnessActivityFeed->Media_Type = 'application/vnd.com.runkeeper.FitnessActivityFeed+json';
$runKeeperConfig->Interfaces->FitnessActivityFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivityFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->FitnessActivityFeed->Read->Url = '/fitnessActivities';
/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->FitnessActivity = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivity->Name = 'FitnessActivity';
$runKeeperConfig->Interfaces->FitnessActivity->Media_Type = 'application/vnd.com.runkeeper.FitnessActivity+json';
$runKeeperConfig->Interfaces->FitnessActivity->Read = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivity->Read->Method = 'GET';
$runKeeperConfig->Interfaces->FitnessActivity->Read->Url = '/fitnessActivities';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->FitnessActivityUpdate = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivityUpdate->Name = 'FitnessActivity';
$runKeeperConfig->Interfaces->FitnessActivityUpdate->Media_Type = 'application/vnd.com.runkeeper.FitnessActivity+json';
$runKeeperConfig->Interfaces->FitnessActivityUpdate->Update = new stdClass();
$runKeeperConfig->Interfaces->FitnessActivityUpdate->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->FitnessActivityUpdate->Update->Url = '/fitnessActivities';
/**
 * Create:
 */
$runKeeperConfig->Interfaces->NewFitnessActivity = new stdClass();
$runKeeperConfig->Interfaces->NewFitnessActivity->Name = 'NewFitnessActivity';
$runKeeperConfig->Interfaces->NewFitnessActivity->Media_Type = 'application/vnd.com.runkeeper.NewFitnessActivity+json';
$runKeeperConfig->Interfaces->NewFitnessActivity->Parent = 'FitnessActivity';
$runKeeperConfig->Interfaces->NewFitnessActivity->Create = new stdClass();
$runKeeperConfig->Interfaces->NewFitnessActivity->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewFitnessActivity->Create->Url = '/fitnessActivities';


/**
 * Weight feed
 */
$runKeeperConfig->Interfaces->WeightFeed = new stdClass();
$runKeeperConfig->Interfaces->WeightFeed->Name = 'WeightFeed';
$runKeeperConfig->Interfaces->WeightFeed->Media_Type = 'application/vnd.com.runkeeper.WeightSet+json';
$runKeeperConfig->Interfaces->WeightFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->WeightFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->WeightFeed->Read->Url = '/weight';

/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->Weight = new stdClass();
$runKeeperConfig->Interfaces->Weight->Name = 'Weight';
$runKeeperConfig->Interfaces->Weight->Media_Type = 'application/vnd.com.runkeeper.Weight+json';
$runKeeperConfig->Interfaces->Weight->Read = new stdClass();
$runKeeperConfig->Interfaces->Weight->Read->Method = 'GET';
$runKeeperConfig->Interfaces->Weight->Read->Url = '/weight';

/**
 * create:
 */
$runKeeperConfig->Interfaces->NewWeight = new stdClass();
$runKeeperConfig->Interfaces->NewWeight->Name = 'NewWeight';
$runKeeperConfig->Interfaces->NewWeight->Media_Type = 'application/vnd.com.runkeeper.NewWeightSet+json';
$runKeeperConfig->Interfaces->NewWeight->Create = new stdClass();
$runKeeperConfig->Interfaces->NewWeight->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewWeight->Create->Url = '/weight';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->UpdateWeight = new stdClass();
$runKeeperConfig->Interfaces->UpdateWeight->Name = 'UpdateWeight';
$runKeeperConfig->Interfaces->UpdateWeight->Media_Type = 'application/vnd.com.runkeeper.Weight+json';
$runKeeperConfig->Interfaces->UpdateWeight->Update = new stdClass();
$runKeeperConfig->Interfaces->UpdateWeight->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->UpdateWeight->Update->Url = '/weight';


/**
 * Strength Training activity feed
 */
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed = new stdClass();
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed->Name = 'StrengthTrainingActivityFeed';
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed->Media_Type = 'application/vnd.com.runkeeper.StrengthTrainingActivityFeed+json';
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->StrengthTrainingActivityFeed->Read->Url = '/strengthTrainingActivities';
/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->StrengthTrainingActivity = new stdClass();
$runKeeperConfig->Interfaces->StrengthTrainingActivity->Name = 'StrengthTrainingActivity';
$runKeeperConfig->Interfaces->StrengthTrainingActivity->Media_Type = 'application/vnd.com.runkeeper.StrengthTrainingActivity+json';
$runKeeperConfig->Interfaces->StrengthTrainingActivity->Read = new stdClass();
$runKeeperConfig->Interfaces->StrengthTrainingActivity->Read->Method = 'GET';
$runKeeperConfig->Interfaces->StrengthTrainingActivity->Read->Url = '/strengthTrainingActivities';
/**
 * create:
 */
$runKeeperConfig->Interfaces->NewStrengthActivity = new stdClass();
$runKeeperConfig->Interfaces->NewStrengthActivity->Name = 'NewStrengthActivity';
$runKeeperConfig->Interfaces->NewStrengthActivity->Media_Type = 'application/vnd.com.runkeeper.NewStrengthTrainingActivity+json';
$runKeeperConfig->Interfaces->NewStrengthActivity->Create = new stdClass();
$runKeeperConfig->Interfaces->NewStrengthActivity->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewStrengthActivity->Create->Url = '/strengthTrainingActivities';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->UpdateStrengthActivity = new stdClass();
$runKeeperConfig->Interfaces->UpdateStrengthActivity->Name = 'UpdateStrengthActivity';
$runKeeperConfig->Interfaces->UpdateStrengthActivity->Media_Type = 'application/vnd.com.runkeeper.StrengthTrainingActivity+json';
$runKeeperConfig->Interfaces->UpdateStrengthActivity->Update = new stdClass();
$runKeeperConfig->Interfaces->UpdateStrengthActivity->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->UpdateStrengthActivity->Update->Url = '/strengthTrainingActivities';


/**
 * Nutrition activity feed
 */
$runKeeperConfig->Interfaces->NutritionSetFeed = new stdClass();
$runKeeperConfig->Interfaces->NutritionSetFeed->Name = 'NutritionSetFeed';
$runKeeperConfig->Interfaces->NutritionSetFeed->Media_Type = 'application/vnd.com.runkeeper.NutritionSetFeed+json';
$runKeeperConfig->Interfaces->NutritionSetFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->NutritionSetFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->NutritionSetFeed->Read->Url = '/nutrition';
/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->NutritionSet = new stdClass();
$runKeeperConfig->Interfaces->NutritionSet->Name = 'NutritionSet';
$runKeeperConfig->Interfaces->NutritionSet->Media_Type = 'application/vnd.com.runkeeper.NutritionSet+json';
$runKeeperConfig->Interfaces->NutritionSet->Read = new stdClass();
$runKeeperConfig->Interfaces->NutritionSet->Read->Method = 'GET';
$runKeeperConfig->Interfaces->NutritionSet->Read->Url = '/nutrition';
/**
 * create:
 */
$runKeeperConfig->Interfaces->NewNutritionSet = new stdClass();
$runKeeperConfig->Interfaces->NewNutritionSet->Name = 'NewNutritionSet';
$runKeeperConfig->Interfaces->NewNutritionSet->Media_Type = 'application/vnd.com.runkeeper.NewNutritionSet+json';
$runKeeperConfig->Interfaces->NewNutritionSet->Create = new stdClass();
$runKeeperConfig->Interfaces->NewNutritionSet->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewNutritionSet->Create->Url = '/nutrition';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->UpdateNutritionSet = new stdClass();
$runKeeperConfig->Interfaces->UpdateNutritionSet->Name = 'UpdateNutritionSet';
$runKeeperConfig->Interfaces->UpdateNutritionSet->Media_Type = 'application/vnd.com.runkeeper.NutritionSet+json';
$runKeeperConfig->Interfaces->UpdateNutritionSet->Update = new stdClass();
$runKeeperConfig->Interfaces->UpdateNutritionSet->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->UpdateNutritionSet->Update->Url = '/nutrition';


/**
 * Background activity feed
 */
$runKeeperConfig->Interfaces->BackgroundActivityFeed = new stdClass();
$runKeeperConfig->Interfaces->BackgroundActivityFeed->Name = 'BackgroundActivityFeed';
$runKeeperConfig->Interfaces->BackgroundActivityFeed->Media_Type = 'application/vnd.com.runkeeper.BackgroundActivityFeed+json';
$runKeeperConfig->Interfaces->BackgroundActivityFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->BackgroundActivityFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->BackgroundActivityFeed->Read->Url = '/backgroundActivities';
/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->BackgroundActivity = new stdClass();
$runKeeperConfig->Interfaces->BackgroundActivity->Name = 'BackgroundActivity';
$runKeeperConfig->Interfaces->BackgroundActivity->Media_Type = 'application/vnd.com.runkeeper.BackgroundActivity+json';
$runKeeperConfig->Interfaces->BackgroundActivity->Read = new stdClass();
$runKeeperConfig->Interfaces->BackgroundActivity->Read->Method = 'GET';
$runKeeperConfig->Interfaces->BackgroundActivity->Read->Url = '/backgroundActivities';
/**
 * create:
 */
$runKeeperConfig->Interfaces->NewBackgroundActivity = new stdClass();
$runKeeperConfig->Interfaces->NewBackgroundActivity->Name = 'NewBackgroundActivity';
$runKeeperConfig->Interfaces->NewBackgroundActivity->Media_Type = 'application/vnd.com.runkeeper.NewBackgroundActivitySet+json';
$runKeeperConfig->Interfaces->NewBackgroundActivity->Create = new stdClass();
$runKeeperConfig->Interfaces->NewBackgroundActivity->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewBackgroundActivity->Create->Url = '/backgroundActivities';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->UpdateBackgroundActivity = new stdClass();
$runKeeperConfig->Interfaces->UpdateBackgroundActivity->Name = 'UpdateBackgroundActivity';
$runKeeperConfig->Interfaces->UpdateBackgroundActivity->Media_Type = 'application/vnd.com.runkeeper.BackgroundActivity+json';
$runKeeperConfig->Interfaces->UpdateBackgroundActivity->Update = new stdClass();
$runKeeperConfig->Interfaces->UpdateBackgroundActivity->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->UpdateBackgroundActivity->Update->Url = '/backgroundActivities';


/**
 * General Measurement feed
 */
$runKeeperConfig->Interfaces->GeneralMeasurementFeed = new stdClass();
$runKeeperConfig->Interfaces->GeneralMeasurementFeed->Name = 'GeneralMeasurementFeed';
$runKeeperConfig->Interfaces->GeneralMeasurementFeed->Media_Type = 'application/vnd.com.runkeeper.GeneralMeasurementSetFeed+json';
$runKeeperConfig->Interfaces->GeneralMeasurementFeed->Read = new stdClass();
$runKeeperConfig->Interfaces->GeneralMeasurementFeed->Read->Method = 'GET';
$runKeeperConfig->Interfaces->GeneralMeasurementFeed->Read->Url = '/generalMeasurements';
/**
 * Read Single:
 */
$runKeeperConfig->Interfaces->GeneralMeasurement = new stdClass();
$runKeeperConfig->Interfaces->GeneralMeasurement->Name = 'GeneralMeasurement';
$runKeeperConfig->Interfaces->GeneralMeasurement->Media_Type = 'application/vnd.com.runkeeper.GeneralMeasurementSet+json';
$runKeeperConfig->Interfaces->GeneralMeasurement->Read = new stdClass();
$runKeeperConfig->Interfaces->GeneralMeasurement->Read->Method = 'GET';
$runKeeperConfig->Interfaces->GeneralMeasurement->Read->Url = '/generalMeasurements';
/**
 * create:
 */
$runKeeperConfig->Interfaces->NewGeneralMeasurement = new stdClass();
$runKeeperConfig->Interfaces->NewGeneralMeasurement->Name = 'NewGeneralMeasurement';
$runKeeperConfig->Interfaces->NewGeneralMeasurement->Media_Type = 'application/vnd.com.runkeeper.NewGeneralMeasurementSet+json';
$runKeeperConfig->Interfaces->NewGeneralMeasurement->Create = new stdClass();
$runKeeperConfig->Interfaces->NewGeneralMeasurement->Create->Method = 'POST';
$runKeeperConfig->Interfaces->NewGeneralMeasurement->Create->Url = '/generalMeasurements';
/**
 * Update:
 */
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement = new stdClass();
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement->Name = 'UpdateGeneralMeasurement';
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement->Media_Type = 'application/vnd.com.runkeeper.GeneralMeasurementSet+json';
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement->Update = new stdClass();
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement->Update->Method = 'PUT';
$runKeeperConfig->Interfaces->UpdateGeneralMeasurement->Update->Url = '/generalMeasurements';
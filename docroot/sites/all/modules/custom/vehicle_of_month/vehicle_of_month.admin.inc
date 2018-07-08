<?php

/*
 * Implements hook_form() for admin form
 */
function vehicle_of_month_form($form, &$form_state){
	$form = array();
	$form['cg_vehicle_name'] = array(
			'#title' => t('Vehicle name'),
			'#default_value' => variable_get( 'cg_vehicle_name', '' ),
			'#size' => 60,
			'#maxlength' => 128,
	        '#required' => TRUE,
			'#description' => t('Vehicle Name'),
			'#type' => 'textfield',
	);

	$form['cg_vehicle_url'] = array(
			'#title' => t('Vehicle URL'),
			'#default_value' => variable_get('cg_vehicle_url', ''),
			'#size' => 60,
			'#maxlength' => 255,
	        '#required' => true,
	        '#type' => 'textfield',
	        '#description' => t('Internal URL to vehicle page'),
	);
	

	$form['cg_vehicle_image'] = array(
			'#type' => 'managed_file',
			'#name' => 'cg_vehicle_image',
			'#title' => t('Vehicle Image'),
			'#size' => 40,
			'#upload_location' => 'public://images/vehicle',
			'#default_value' => variable_get('cg_vehicle_image', ''),
			'#required' => TRUE,
			'#upload_validators' => array(
					'file_validate_extensions' => array('gif png jpg jpeg'),
			    'file_validate_image_resolution' => array('173x173', '100x100')
			)
	);

	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Save settings'),
	);
	return $form;
}

/**
 * implement hook_form_submit
 */
function vehicle_of_month_form_submit($form, &$form_state) {
	if (isset($form_state['values']['cg_vehicle_image']) && !empty($form_state['values']['cg_vehicle_image'])) {
		$file = file_load($form_state['values']['cg_vehicle_image']);
		if ($file) {
			$file->status = FILE_STATUS_PERMANENT;
			file_save($file);
			file_usage_add($file, 'cg_vehicle_image', 'managed_file', $file->fid);
		}
	}
	variable_set( 'cg_vehicle_name', $form_state['values']['cg_vehicle_name'] );
	variable_set( 'cg_vehicle_url', $form_state['values']['cg_vehicle_url'] );
	variable_set( 'cg_vehicle_image', $form_state['values']['cg_vehicle_image'] );
	
	drupal_set_message( t('Settings saved successfully!') );
}

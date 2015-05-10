<?php
/**
 * @file
 * Functions for the XML To Form module (used by module and tests)
 */

/**
 * XML To Form public form constructor
 *
 * Read in XML and construct a form.
 *
 * @param $form
 *   A structured array containing the elements and properties of the form.
 *
 * @return $form
 *
 * @see xmltoform_public_form()
 * @ingroup forms
 *
 * @todo Get page title from a configurable variable
 * @todo Loop over multiple fieldsets
 * 
 */
function xmltoform_public_formconstruct($form) {

#  $site_date_format = variable_get('date_format_short', 'd/m/Y - H:i');
#  print_r(system_get_date_formats());

  if (file_exists(drupal_get_path('module', 'xmltoform') . '/form.xml')) {
    $xml = simplexml_load_file(drupal_get_path('module', 'xmltoform') . '/form.xml');
	 // Set page title from fieldset title (for now)
	 if (isset($xml->fieldset->title)) {
		$page_title = (string) $xml->fieldset->title;
		drupal_set_title($page_title);
	 }
    if (isset($xml->fieldset->fields->field[0])) {
		$fields = $xml->fieldset->fields->field;
	   foreach($fields as $field) {
		  $name = (string) $field->name;
		  $form['xmltoform_' . $name] = array();
		  $type = ($field->type == "text") ? "textfield" : (string) $field->type;
		  $type = ($field->type == "radio") ? "radios" : $type;
		  $form['xmltoform_' . $name]['#type'] = $type;
		  $form['xmltoform_' . $name]['#title'] = (string) $field->label;
		  if (isset($field->default_value)) {
		    if ($type == "date") {
				$date = (string) $field->default_value;
				$form['xmltoform_' . $name]['#type'] = "date_popup";
				#$form['xmltoform_' . $name]['#date_format'] = "d/m/Y";
				$form['xmltoform_' . $name]['#default_value'] = $date . ' 00:00';
			 } else {
				$form['xmltoform_' . $name]['#default_value'] = (string) $field->default_value;
			 }
		  }
		  $required = ((int) $field->required) ? TRUE : FALSE;
		  $form['xmltoform_' . $name]['#required'] = $required;
		  if (isset($field->maxlen)) {
		    $form['xmltoform_' . $name]['#size'] = (string) $field->maxlen;
		    $form['xmltoform_' . $name]['#maxlength'] = (string) $field->maxlen;
		  }
		  if (isset($field->options)) {
		    $form['xmltoform_' . $name]['#options'] = array();
   		 foreach($field->options->option as $option) {
				if (isset($option->text)) {
				  $form['xmltoform_' . $name]['#options'][(string) $option->value] = (string) $option->text;
				} else {
				  $form['xmltoform_' . $name]['#options'][] = (string) $option;
				}
			 }
		  }
		}
	 }
  }
  #print_r($form);
  // Provide a customised submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit details',
  );
  
  return($form);
}

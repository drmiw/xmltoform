<?php
/**
 * @file
 * Functions for the XML To Form module (used by module and tests).
 */

/**
 * XML To Form public form constructor.
 *
 * Read in XML and construct a form.
 *
 * @param array $form
 *   A structured array containing the elements and properties of the form.
 *
 * @return array $form
 *   A generated form with fields as defined in the XML file.
 *
 * @see xmltoform_public_form()
 *
 * @ingroup forms
 *
 * @todo Get page title from a configurable variable
 * @todo Loop over multiple fieldsets
 */
function xmltoform_public_formconstruct(array $form) {

  if (file_exists(drupal_get_path('module', 'xmltoform') . '/form.xml')) {
    $xml = simplexml_load_file(drupal_get_path('module', 'xmltoform') . '/form.xml');
    // Set page title from fieldset title (for now).
    if (isset($xml->fieldset->title)) {
      $page_title = (string) $xml->fieldset->title;
      drupal_set_title($page_title);
    }
    if (isset($xml->fieldset->fields->field[0])) {
      $fields = $xml->fieldset->fields->field;
      foreach ($fields as $field) {
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
            // Use site date format but could set ['#date_format'] = "d/m/Y";
            // Note: variable_get('date_format_short', 'd/m/Y - H:i');
            $form['xmltoform_' . $name]['#default_value'] = $date . ' 00:00';
          }
          else {
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
          foreach ($field->options->option as $option) {
            if (isset($option->text)) {
              $form['xmltoform_' . $name]['#options'][(string) $option->value] = (string) $option->text;
            }
            else {
              $form['xmltoform_' . $name]['#options'][] = (string) $option;
            }
          }
        }
      }
    }
  }
  // Provide a customised submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit details',
  );

  return ($form);
}

/**
 * Added MyDateTime to support PHP versions < 5.3.
 */
class MyDateTime extends DateTime {
  /**
   * Emulate DateTime:createFromFormat for PHP < 5.3.
   */
  public static function createFromFormat($format, $time, $timezone = NULL) {

    if (!$timezone) {
      $timezone = new DateTimeZone(date_default_timezone_get());
    }
    $version = explode('.', phpversion());
    if (((int) $version[0] >= 5 && (int) $version[1] >= 2 && (int) $version[2] > 17)) {
      return parent::createFromFormat($format, $time, $timezone);
    }
    return new DateTime(date($format, strtotime($time)), $timezone);
  }

}

<?php

function sendinblue_rules_admin_settings_form($form, &$form_state) {
  $form['sendinblue_rules_api_v3_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API v3 Key'),
    '#description' => t('Key for API v3.'),
    '#default_value' => variable_get('sendinblue_rules_api_v3_key', NULL),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function sendinblue_rules_admin_settings_form_validate($form, &$form_state) {
  $api_key = $form_state['values']['sendinblue_rules_api_v3_key'];
  $mailin = new SendinblueMailin(SENDINBLUE_API_V3_URL, $api_key);
  $result = $mailin->get('account', NULL);
  if (empty($result['plan'])) {
    form_set_error('sendinblue_rules_api_v3_key', t('API v3 key is invalid. Please provide a valid one.'));
  }
}

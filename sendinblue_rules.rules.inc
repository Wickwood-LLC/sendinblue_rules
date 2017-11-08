<?php

/**
 * UI for SendinBlue Attribute.
 */
class SendinBlueAttributeRulesDataUI extends RulesDataUI implements RulesDataDirectInputFormInterface {

  public static function getDefaultMode() {
    return 'input';
  }

  public static function inputForm($name, $info, $settings, RulesPlugin $element) {
    $settings += array($name => isset($info['default value']) ? $info['default value'] : array('name' => NULL, 'value' => NULL));

    $form[$name]['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute name'),
      '#default_value' => $settings[$name]['name'],
      '#required' => TRUE,
    );
    $form[$name]['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute value'),
      '#default_value' => $settings[$name]['value'],
      '#required' => TRUE,
    );
    return $form;
  }

  public static function render($value) {
    return array(
      'content' => array('#markup' => t('(name: @name, value: @value)', array('@name' => $value['name'], '@value' => $value['value']))),
      '#attributes' => array('class' => array('rules-sendinblue-attribute')),
    );
  }
}

/**
 * Implements hook_rules_data_info().
 */
function sendinblue_rules_rules_data_info() {
  return array(
    'sendinblue_attribute' => array(
      'label' => t('SendinBlue Attribute'),
      'group' => t('SendinBlue'),
      'ui class' => 'SendinBlueAttributeRulesDataUI',
      'property info' => array(
        'name' => array(
          'type' => 'text',
          'label' => t('Attribute Name'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'value' => array(
          'type' => 'text',
          'label' => t('Attribute Value'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_action_info()
 */
function sendinblue_rules_rules_action_info() {
  $items = array();

  $items['sendinblue_create_contact'] = array(
    'label' => t('Create a SendinBlue contact'),
    'parameter' => array(
      'account' => array('type' => 'user', 'label' => t('Subscriber')),
      'lists' => array(
        'type' => 'list<text>',
        'label' => t('Lists'),
        'options list' => 'sendinblue_rules_lists_options',
        'optional' => TRUE,
      ),
      'attributes' => array(
        'type' => 'list<sendinblue_attribute>',
        'label' => t('Attributes'),
        'optional' => TRUE,
      ),
      'updateEnabled' => array(
        'type' => 'boolean',
        'label' => t('Update enabled'),
        'description' => t('Facilitate to update existing contact in same request.'),
        'optional' => TRUE,
      ),
    ),
    'group' => t('SendinBlue'),
  );

  $items['sendinblue_update_contact'] = array(
    'label' => t('Update a SendinBlue contact'),
    'parameter' => array(
      'email' => array('type' => 'text', 'label' => t('Email')),
      'attributes' => array(
        'type' => 'list<sendinblue_attribute>',
        'label' => t('Attributes'),
        'description' => t('Values of the attributes to fill. The attributes must exist in you contact database'),
        'optional' => TRUE,
      ),
      'listIds' => array(
        'type' => 'list<text>',
        'label' => t('Lists to add to'),
        'options list' => 'sendinblue_rules_lists_options',
        'description' => t('Ids of the lists to add the contact to'),
        'optional' => TRUE,
      ),
      'unlinkListIds' => array(
        'type' => 'list<text>',
        'label' => t('Lists to remove from'),
        'options list' => 'sendinblue_rules_lists_options',
        'description' => t('Ids of the lists to remove the contact from'),
        'optional' => TRUE,
      )
    ),
    'group' => t('SendinBlue'),
  );

  $items['sendinblue_attribute_add_to_list'] = array(
    'label' => t('Add SendinBlue attribute to list'),
    'parameter' => array(
      'attributes' => array(
        'type' => 'list<sendinblue_attribute>',
        'label' => t('Attributes List'),
        'save' => TRUE,
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('Attribute Name'),
      ),
      'value' => array(
        'type' => 'text',
        'label' => t('Attribute Value'),
      ),
    ),
    'group' => t('SendinBlue'),
  );

  $items['sendinblue_retrieve_contact_info'] = array(
    'label' => t('Retrieve SendinBlue contact info'),
    'parameter' => array(
      'email' => array(
        'type' => 'text',
        'label' => t('Email address'),
      ),
    ),
    'provides' => array(
      'contact_info' => array(
        'type' => 'text',
        'label' => t('Serialized contact info')
      ),
    ),
    'group' => t('SendinBlue'),
  );
  
  $items['sendinblue_list_add_remove_contacts'] = array(
    'label' => t('Add/remove SendinBlue contacts to/from list'),
    'parameter' => array(
      'emails' => array(
        'type' => 'list<text>',
        'label' => t('Email addresses'),
      ),
      'list' => array(
        'type' => 'text',
        'label' => t('List ID'),
      ),
      'operation' => array(
        'type' => 'text',
        'label' => t('Action'),
        'options list' => 'sendinblue_rules_lists_action_options',
      ),
    ),
    'group' => t('SendinBlue'),
  );

  return $items;
}

function sendinblue_rules_lists_options() {
  module_load_include('inc', 'sendinblue_rules', 'includes/sendinblue_rules.list');
  $options = array();
  foreach (sendinblue_rules_get_lists() as $list) {
    $options[$list['id']] = $list['name'];
  }
  return $options;
}

function sendinblue_create_contact($account, $lists, $attributes, $updateEnabled) {
  $success = false;
  
  $mailin = sendinblue_rules_get_client();
  $data = array();

  foreach ($attributes as $attribute) {
    $data['attributes'][$attribute['name']] = $attribute['value'];
  }

  $data['listid'] = array();
  foreach ($lists as $list) {
    $data['listid'][] = $list;
  }
  if ($updateEnabled === TRUE) {
    $data['updateEnabled'] = TRUE;
  }

  $data['email'] = $account->mail;
  $result = $mailin->post('contacts', json_encode($data));
  $success = isset($result['id']);

  if (!$success) {
    watchdog('sendinblue', t('Contact for email @email could not be created', array('@email' => $account->mail)));
  }
}

function sendinblue_update_contact($email, $attributes, $listIds, $unlinkListIds) {
  module_load_include('inc', 'sendinblue_rules', 'includes/sendinblue_rules.list');
  $all_lists = sendinblue_rules_get_lists();
  $success = false;
  
  $mailin = sendinblue_rules_get_client();
  $data = array();

  $attributes = is_array($attributes) ? $attributes : array();
  foreach ($attributes as $attribute) {
    $data['attributes'][$attribute['name']] = $attribute['value'];
  }

  $data['listid'] = is_array($listIds) ? $listIds : array();
  $data['unlinkListIds'] = is_array($unlinkListIds) ? $unlinkListIds : array();

  $result = $mailin->put("contacts/{$email}" , $data);
  // TODO: determine success.
  $success = TRUE;

  if (!$success) {
    watchdog('sendinblue', t('Contact for email @email could not be updated', array('@email' => $email)));
  }
}

/**
 * Rules action callback.
 */
function sendinblue_attribute_add_to_list($attributes, $name, $value) {
  $attributes[] = array ('name' => $name, 'value' => $value);
  return array('attributes' => $attributes);
}

function sendinblue_retrieve_contact_info($email) {
  $contact_info = NULL;
  $mailin = sendinblue_rules_get_client();
  $result = $mailin->get("contacts/{$email}" , NULL);
  if (isset($result['email'])) {
    $contact_info = serialize($result);
  }

  return array('contact_info' => $contact_info);
}

function sendinblue_rules_lists_action_options() {
  return array(
    'add' => t('Add'),
    'remove' => t('Remove'),
  );
}

function sendinblue_list_add_remove_contact($emails, $list, $operation) {
  $mailin = sendinblue_rules_get_client();
  $result = $mailin->post("contacts/lists/{$list}/contacts/{$operation}" , array('emails' => $emails));
  // TODO: determine success.
}
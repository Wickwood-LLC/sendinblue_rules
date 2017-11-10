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
    'sendinblue_message_sent_event' => array(
      'label' => t('SendinBlue Message Sent Event'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property info' => array(
        'campaignId' => array(
          'type' => 'int',
          'label' => t('Campaign Id'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'eventTime' => array(
          'type' => 'text',
          'label' => t('Event Time'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
    'sendinblue_opened_event' => array(
      'label' => t('SendinBlue Opened Event'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property info' => array(
        'campaignId' => array(
          'type' => 'int',
          'label' => t('Campaign Id'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'count' => array(
          'type' => 'int',
          'label' => t('Count'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'eventTime' => array(
          'type' => 'text',
          'label' => t('Event Time'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'ip' => array(
          'type' => 'text',
          'label' => t('IP'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
    'sendinblue_clicked_event' => array(
      'label' => t('SendinBlue Clicked Event'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property info' => array(
        'count' => array(
          'type' => 'int',
          'label' => t('Count'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'eventTime' => array(
          'type' => 'text',
          'label' => t('Event Time'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'ip' => array(
          'type' => 'text',
          'label' => t('IP'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'url' => array(
          'type' => 'text',
          'label' => t('URL'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
    'sendinblue_clicked' => array(
      'label' => t('SendinBlue Clicked'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property info' => array(
        'campaignId' => array(
          'type' => 'int',
          'label' => t('Campaign Id'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'links' => array(
          'type' => 'list<sendinblue_clicked_event>',
          'label' => t('Links'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
    'sendinblue_statistics' => array(
      'label' => t('SendinBlue Statistics'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property info' => array(
        'messagesSent' => array(
          'type' => 'list<sendinblue_message_sent_event>',
          'label' => t('Messages Sent'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'opened' => array(
          'type' => 'list<sendinblue_opened_event>',
          'label' => t('Opens'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'clicked' => array(
          'type' => 'list<sendinblue_clicked>',
          'label' => t('Clicks'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
      ),
    ),
    'sendinblue_contact' => array(
      'label' => t('SendinBlue Contact'),
      'group' => t('SendinBlue'),
      'wrapper class' => 'SendinBlueAssociativeArrayWrapper',
      'wrap' => TRUE,
      'property defaults' => array(
        'email' => NULL,
        'id' => NULL,
        'emailBlacklisted' => NULL,
        'smsBlacklisted' => NULL,
        'modifiedAt' => NULL,
        'attributes' => array(),
        'smsBlacklisted' => NULL,
        'listIds' => array(),
        'statistics' => NULL,
      ),
      'property info' => array(
        'email' => array(
          'type' => 'text',
          'label' => t('Email'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'id' => array(
          'type' => 'int',
          'label' => t('ID'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'emailBlacklisted' => array(
          'type' => 'boolean',
          'label' => t('Email blacklisted'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'smsBlacklisted' => array(
          'type' => 'boolean',
          'label' => t('SMS blacklisted'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'modifiedAt' => array(
          'type' => 'text',
          'label' => t('Modified at'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'attributes' => array(
          'type' => 'list<sendinblue_attribute>',
          'label' => t('Attributes'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'listIds' => array(
          'type' => 'list<integer>',
          'label' => t('List IDs'),
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
        ),
        'statistics' => array(
          'type' => 'sendinblue_statistics',
          'label' => t('Statistics'),
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
      'email' => array(
        'type' => 'text',
        'label' => t('Email')
      ),
      'attributes' => array(
        'type' => 'list<sendinblue_attribute>',
        'label' => t('Attributes'),
        'optional' => TRUE,
        'description' => t('Values of the attributes to fill. The attributes must exist at SendinBlue contact database')
      ),
      'emailBlacklisted' => array(
        'type' => 'boolean',
        'label' => t('Email blacklisted'),
        'description' => t('Blacklist the contact for emails.'),
        'optional' => TRUE,
      ),
      'smsBlacklisted' => array(
        'type' => 'boolean',
        'label' => t('SMS blacklisted'),
        'description' => t('Blacklist the contact for SMS.'),
        'optional' => TRUE,
      ),
      'lists' => array(
        'type' => 'list<integer>',
        'label' => t('Lists'),
        'options list' => 'sendinblue_rules_lists_options',
        'optional' => TRUE,
        'description' => t('Ids of the lists to add the contact to'),
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
        'type' => 'list<integer>',
        'label' => t('Lists to add to'),
        'options list' => 'sendinblue_rules_lists_options',
        'description' => t('Ids of the lists to add the contact to'),
        'optional' => TRUE,
      ),
      'unlinkListIds' => array(
        'type' => 'list<integer>',
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
        'allow null' => TRUE,
      ),
    ),
    'group' => t('SendinBlue'),
  );

  $items['sendinblue_attribute_remove_from_list'] = array(
    'label' => t('Remove SendinBlue attribute from list'),
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
        'type' => 'sendinblue_contact',
        'label' => t('SendinBlue contact info')
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

/**
 * Implements hook_rules_condition_info().
 */
function sendinblue_rules_rules_condition_info() {
  return array(
    'sendinblue_is_contact_info_valid' => array(
      'label' => t('Is valid SendinBlue contact info'),
      'parameter' => array(
        'contact' => array(
          'label' => t('SendinBlue Contact'),
          'type' => 'sendinblue_contact',
          'allow null' => TRUE,
        ),
      ),
      'group' => t('SendinBlue'),
    ),
  );
}

function sendinblue_rules_lists_options() {
  module_load_include('inc', 'sendinblue_rules', 'includes/sendinblue_rules.list');
  $options = array();
  foreach (sendinblue_rules_get_lists() as $list) {
    $options[(int)$list['id']] = $list['name'];
  }
  return $options;
}

function sendinblue_create_contact($email, $attributes, $emailBlacklisted, $smsBlacklisted, $lists, $updateEnabled) {
  
  $mailin = sendinblue_rules_get_client();
  $data = array();

  foreach ($attributes as $attribute) {
    $data['attributes'][$attribute['name']] = $attribute['value'];
  }

  if ($emailBlacklisted === TRUE) {
    $data['emailBlacklisted'] = TRUE;
  }
  if ($smsBlacklisted === TRUE) {
    $data['smsBlacklisted'] = TRUE;
  }

  $data['listIds'] = is_array($lists) ? array_values(array_map('intval', $lists)) : array();

  if ($updateEnabled === TRUE) {
    $data['updateEnabled'] = TRUE;
  }

  $data['email'] = $email;
  $result = $mailin->post('contacts', json_encode($data));
  $success = isset($result['id']);

  if (!$success) {
    watchdog('sendinblue', t('Contact for email @email could not be created', array('@email' => $account->mail)));
  }
}

function sendinblue_update_contact($email, $attributes, $listIds, $unlinkListIds) {
  module_load_include('inc', 'sendinblue_rules', 'includes/sendinblue_rules.list');
  $all_lists = sendinblue_rules_get_lists();
  
  $mailin = sendinblue_rules_get_client();
  $data = array();

  $attributes = is_array($attributes) ? $attributes : array();
  foreach ($attributes as $attribute) {
    $data['attributes'][$attribute['name']] = $attribute['value'];
  }

  $data['listIds'] = is_array($listIds) ? array_values(array_map('intval', $listIds)) : array();
  $data['unlinkListIds'] = is_array($unlinkListIds) ? array_values(array_map('intval', $unlinkListIds)) : array();

  $encoded_email = urlencode($email);
  $result = $mailin->put("contacts/{$encoded_email}" , json_encode($data));
  // Nothing will be return if it was success.
  $success = !isset($result);

  if (!$success) {
    watchdog('sendinblue', t('Contact for email @email could not be updated', array('@email' => $email)));
  }
}

/**
 * Rules action callback.
 */
function sendinblue_attribute_add_to_list($attributes, $name, $value) {
  $attributes[] = array ('name' => $name, 'value' => $value);
  $found = false;
  foreach ($attributes as $index => $attribute) {
    if ($attribute['name'] == $name) {
      $attributes[$index]['value'] = $value;
      $found = TRUE;
    }
  }

  if (!$found) {
    $attributes[] = array('name' => $name, 'value' => $value);
  }
  return array('attributes' => $attributes);
}

function sendinblue_attribute_remove_from_list($attributes, $name) {
  foreach ($attributes as $index => $attribute) {
    if ($attribute['name'] == $name) {
      unset($attributes[$index]);
      break;
    }
  }
  return array('attributes' => $attributes);
}

function sendinblue_retrieve_contact_info($email) {
  $contact_info = NULL;
  $mailin = sendinblue_rules_get_client();
  $encoded_email = urlencode($email);
  $result = $mailin->get("contacts/{$encoded_email}" , NULL);
  watchdog('sendinblue', print_r($result, TRUE));
  if (isset($result['email'])) {
    $contact_info = $result;
    if (isset($contact_info['attributes'])) {
      // Attributes to be converted to our data type format.
      $attributes = array();
      foreach ($contact_info['attributes'] as $name => $value) {
        $attributes[] = array('name' => $name, 'value' => $value);
      }
      $contact_info['attributes'] = $attributes;
    }
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
  $result = $mailin->post("contacts/lists/{$list}/contacts/{$operation}" , json_encode(array('emails' => $emails)));
  // TODO: determine success.
}

function sendinblue_is_contact_info_valid($contact) {
  return isset($contact['id']);
}
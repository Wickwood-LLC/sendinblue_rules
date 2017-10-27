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

  $items['sendinblue_add_user_to_list'] = array(
    'label' => t('Add a user to lists'),
    'parameter' => array(
      'account' => array('type' => 'user', 'label' => t('Subscriber')),
      'lists' => array(
        'type' => 'list<text>',
        'label' => t('Lists'),
        'options list' => 'sendinblue_rules_lists_options',
      ),
      'attributes' => array(
        'type' => 'list<sendinblue_attribute>',
        'label' => t('Attributes'),
      ),
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

function sendinblue_add_user_to_list($account, $lists, $attributes) {
  module_load_include('inc', 'sendinblue_rules', 'includes/sendinblue_rules.list');
  $all_lists = sendinblue_rules_get_lists();
  
  $mailin = sendinblue_rules_get_client();
  $data = array();
  $data['email'] = $account->mail;
  foreach ($attributes as $attribute) {
    $data['attributes'][$attribute['name']] = $attribute['value'];
  }

  $data['listid'] = array();
  foreach ($lists as $list) {
    $data['listid'][] = $list;
  }
  
  $result = $mailin->post('user/createdituser', $data);
  if (!isset($result['code']) || $result['code'] != 'success') {
    $names = array();
    foreach ($lists as $list_id) {
      $names[] = "{$all_lists[$list_id]['name']} ($list_id)";
    }
    watchdog(
      'sendinblue',
      t(
        'User @username (@uid) could not be added to mailing list(s): @lists.',
        array(
          '@username' => $account->name, '@uid' => $account->uid,
          '@lists' => implode(' ', $names),
        )
      )
    );
  }
}

/**
 * Rules action callback.
 */
function sendinblue_attribute_add_to_list($attributes, $name, $value) {
  $attributes[] = array ('name' => $name, 'value' => $value);
  return array('attributes' => $attributes);
}


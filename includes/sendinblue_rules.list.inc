<?php


function sendinblue_rules_get_lists() {
  $lists = array();

  if ($cache = cache_get('sendinblue_rules_lists') && REQUEST_TIME < $cache->expire) {
    $lists = $cache->data;
  }
  else {
    $mailin = sendinblue_rules_get_client();
    $result = $mailin->get('list', NULL);
    if (isset($result['code']) && $result['code'] == 'success') {
      foreach ($result['data'] as $list_info) {
        $lists[$list_info['id']] = $list_info;
      }
    }
    // Stores in cache table and expires after 1 day.
    cache_set('sendinblue_rules_lists', $data, 'cache',  REQUEST_TIME  + (3600 * 24));
  }

  return $lists;
}

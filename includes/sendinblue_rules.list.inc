<?php


function sendinblue_rules_get_lists() {
  $lists = array();
  $cache = cache_get('sendinblue_rules_lists');
  if ($cache && REQUEST_TIME < $cache->expire) {
    $lists = $cache->data;
  }
  else {
    $mailin = sendinblue_rules_get_client();
    $result = $mailin->get('contacts/lists', NULL);
    if (isset($result['lists'])) {
      foreach ($result['lists'] as $list_info) {
        $lists[$list_info['id']] = $list_info;
      }
    }
    // Stores in cache table and expires after 1 day.
    cache_set('sendinblue_rules_lists', $lists, 'cache',  REQUEST_TIME  + (3600 * 24));
  }

  return $lists;
}

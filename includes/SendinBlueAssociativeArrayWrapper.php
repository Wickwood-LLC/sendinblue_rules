<?php

/**
 * Class to wrap associative array type data types.
 */
class SendinBlueAssociativeArrayWrapper extends EntityStructureWrapper {
  /**
   * Sets a property.
   */
  protected function setProperty($name, $value) {
    $data = $this->value();
    if (!isset($data)) {
      $this->set(array());
    }
    parent::setProperty($name, $value);
  }
}

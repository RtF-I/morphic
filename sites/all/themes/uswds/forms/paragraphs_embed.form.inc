<?php

/**
 * @file
 * Alterations for this form.
 */

/**
 * Implements hook_field_widget_WIDGET_TYPE_form_alter().
 */
function uswds_field_widget_paragraphs_embed_form_alter(&$element, &$form_state, $context) {

  // This adds a class that our custom CSS looks for, to match the D8 behavior.
  if (!empty($element[0]['paragraph_bundle_title'])) {
    $element[0]['paragraph_bundle_title']['#attributes']['class'][] = 'paragraph-type-title';
  }

  // Give the "Remove" button a different look.
  if (!empty($element[0]['actions'])) {
    foreach (element_children($element[0]['actions']) as $key) {
      $element[0]['actions'][$key]['#attributes']['class'][] = 'usa-button-outline';
    }
  }
}

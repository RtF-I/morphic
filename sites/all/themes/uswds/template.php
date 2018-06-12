<?php
/**
 * @file
 * Theme code, mostly to make Drupal 7's markup work with USWDS.
 *
 * Note: If you are looking for theme overrides or preprocess functions, check
 * the uswds/theme and uswds/preprocess folders.
 */

// Bring in our includes. Constants must be required first.
require_once dirname(__FILE__) . '/includes/constants.inc';
require_once dirname(__FILE__) . '/includes/base_themes.inc';
require_once dirname(__FILE__) . '/includes/forms.inc';
require_once dirname(__FILE__) . '/includes/menus.inc';

// Include all our form alter hooks.
$files = file_scan_directory(dirname(__FILE__) . '/forms', '/.form.inc/');
foreach ($files as $filepath => $file) {
  require_once $filepath;
}

/**
 * Implements hook_block_view_alter().
 *
 * This is used to tell what region a block is placed in, and is what allows us
 * to automatically tweak the markup of menus, depending on their region.
 */
function uswds_block_view_alter(&$build, &$block) {

  $special_regions = array(
    'sidebar_first',
    'primary_menu',
    'secondary_menu',
    'mobile_menu',
    'footer_menu',
  );
  if (!in_array($block->region, $special_regions)) {
    return;
  }

  if (empty($build['content']) || !is_array($build['content'])) {
    return;
  }

  // Support menu_block blocks.
  if (!empty($build['content']['#content']['#theme_wrappers'][0][0])) {
    if (strpos($build['content']['#content']['#theme_wrappers'][0][0], 'menu_tree__') !== FALSE) {
      _uswds_menu_block_title($block);
      // Check starting depth and calculate a depth offset.
      $menu_depth_offset = $build['content']['#config']['level'] - 1;
      _uswds_mark_navigation_items_by_region($build['content']['#content'], $block->region, $menu_depth_offset);
    }
  }
  // And of course, core menu blocks.
  elseif (!empty($build['content']['#theme_wrappers'][0])) {
    if (strpos($build['content']['#theme_wrappers'][0], 'menu_tree__') !== FALSE) {
      _uswds_menu_block_title($block);
      _uswds_mark_navigation_items_by_region($build['content'], $block->region);
    }
  }
}

/**
 * Implements hook_theme().
 */
function uswds_theme($existing, $type, $theme, $path) {
  return array(
    'government_banner' => array(
      'path' => $path . '/templates/uswds',
      'template' => 'government-banner',
      'variables' => array(
        'image_base' => NULL,
      ),
    ),
  );
}

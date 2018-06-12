<?php

/**
 * @file
 * Utility code related to menus and menu blocks.
 */

/**
 * Helper function to see if a menu is one of our special USWDS menus.
 */
function _uswds_get_region_for_menu($menu_region) {
  // First check for bypass settings.
  $menu_bypass = theme_get_setting('uswds_menu_bypass');
  if (!empty($menu_bypass[$menu_region])) {
    return FALSE;
  }
  $special_menu_regions = array(
    'primary_menu' => USWDS_MENU_REGION_PRIMARY,
    'secondary_menu' => USWDS_MENU_REGION_SECONDARY,
    'mobile_menu' => USWDS_MENU_REGION_MOBILE,
    'footer_menu' => USWDS_MENU_REGION_FOOTER,
    'sidebar_first' => USWDS_MENU_REGION_SIDE,
  );
  if (empty($special_menu_regions[$menu_region])) {
    return FALSE;
  }
  return $special_menu_regions[$menu_region];
}

/**
 * Helper function to recursively mark menu links as being in a certain region.
 *
 * @param array $element
 *   An array of menu objects
 * @param string $region
 *   The machine name for the region
 * @param int $menu_depth_offset
 *   The difference between the depth of the current menu item and the starting
 *   level of the menu block.
 */
function _uswds_mark_navigation_items_by_region(&$element, $region, $menu_depth_offset = 0) {
  foreach (element_children($element) as $key) {
    // Drop a note in all the menu links for later use in uswds_menu_link().
    $element[$key]['#uswds_menu_region'] = $region;
    // Set shift factor for cases using menu_block to output subsection of menu.
    $element[$key]['#uswds_menu_depth_offset'] = $menu_depth_offset;
    // Recurse if there are children.
    if (!empty($element[$key]['#below'])) {
      _uswds_mark_navigation_items_by_region($element[$key]['#below'], $region, $menu_depth_offset);
    }
  }
}

/**
 * Helper function to tell whether a menu tree is one-dimensional (flat).
 */
function _uswds_is_menu_tree_flat($tree) {
  foreach (element_children($tree) as $key) {
    $link = $tree[$key]['#original_link'];
    $menu_depth_offset = $tree[$key]['#uswds_menu_depth_offset'];
    $depth = $link['depth'] - $menu_depth_offset;
    if (1 != $depth || ($link['has_children'] && $link['expanded'])) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Helper function to hide the block title of most menus.
 */
function _uswds_menu_block_title(&$block) {
  if ('sidebar_first' != $block->region) {
    $block->title = '<none>';
  }
}

/**
 * Helper function to get the search box, for insertion into a menu.
 *
 * @return
 *   Rendered search box.
 */
function _uswds_menu_search_box() {
  $search_form = drupal_get_form('search_block_form');
  $search_form['actions']['submit']['#id'] = 'uswds-search';
  $search_box = drupal_render($search_form);
  return $search_box;
}

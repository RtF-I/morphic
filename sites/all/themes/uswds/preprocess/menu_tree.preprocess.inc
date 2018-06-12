<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu_tree().
 */
function uswds_preprocess_menu_tree(&$variables) {

  // To figure out what USWDS menu this should be, we look
  // for a special flag on the menu items.
  $menu_region = FALSE;
  foreach (element_children($variables['#tree']) as $key) {
    if (!empty($variables['#tree'][$key]['#uswds_menu_region'])) {
      $menu_region = $variables['#tree'][$key]['#uswds_menu_region'];
    }
    // We only need to see one.
    break;
  }
  if (!$menu_region) {
    return;
  }

  $uswds_region = _uswds_get_region_for_menu($menu_region);
  if (!$uswds_region) {
    return;
  }

  switch ($uswds_region) {

    // Primary navigation tweaks.
    case USWDS_MENU_REGION_PRIMARY:
      // Our low-tech way of identifying a submenu here.
      $is_submenu = (strpos($variables['tree'], 'usa-accordion-button') === FALSE);
      // Catch the case where the primary navigation is totally flat.
      if ($is_submenu && _uswds_is_menu_tree_flat($variables['#tree'])) {
        $is_submenu = FALSE;
      }
      if ($is_submenu) {
        // If this is a submenu, the wrapper will be handled in our override of
        // theme_menu_link, so only output the tree itself here.
        $variables['uswds_menu_tree_only'] = TRUE;
      }
      else {
        // Otherwise if not a submenu, add a couple of classes.
        $variables['uswds_menu_attributes']['class'][] = 'usa-nav-primary';
        $variables['uswds_menu_attributes']['class'][] = 'usa-accordion';
        // Decide whether to include the search form.
        if (module_exists('search') && theme_get_setting('uswds_search')) {
          // If this is a basic header, we put the search form after the menu.
          if ('basic' == theme_get_setting('uswds_header_style')) {
            $variables['uswds_menu_suffix'] = _uswds_menu_search_box();
          }
        }
      }
      break;

    // Secondary navigation tweaks.
    case USWDS_MENU_REGION_SECONDARY:
      $variables['uswds_menu_attributes']['class'][] = 'usa-unstyled-list';
      $variables['uswds_menu_attributes']['class'][] = 'usa-nav-secondary-links';
      $variables['uswds_menu_prefix'] = '<div class="usa-nav-secondary">';
      $variables['uswds_menu_suffix'] = '</div>';
      // Decide whether to include the search form.
      if (module_exists('search') && theme_get_setting('uswds_search')) {
        // If this is an extended header, we put the search form before the menu.
        if ('extended' == theme_get_setting('uswds_header_style')) {
          $variables['uswds_menu_prefix'] .= _uswds_menu_search_box();
          // And we also add an extra item at the beginning of the menu.
          $search_item = '<li class="js-search-button-container"><button class="usa-header-search-button js-search-button">Search</button></li>';
          $variables['tree'] = $search_item . $variables['tree'];
        }
      }
      break;

    // Side navigation tweaks.
    case USWDS_MENU_REGION_SIDE:
      $is_submenu = (strpos($variables['tree'], 'uswds-side-nav-top') === FALSE);
      // Catch the case where the side navigation navigation is totally flat.
      if ($is_submenu && _uswds_is_menu_tree_flat($variables['#tree'])) {
        $is_submenu = FALSE;
      }
      if ($is_submenu) {
        $variables['uswds_menu_attributes']['class'][] = 'usa-sidenav-sub_list';
      }
      else {
        $variables['uswds_menu_attributes']['class'][] = 'usa-sidenav-list';
        $variables['uswds_menu_attributes']['class'][] = 'usa-accordion';
      }
      break;

    // Mobile navigation tweaks.
    case USWDS_MENU_REGION_MOBILE:
      $is_submenu = (!empty($variables['#tree']['#uswds_menu_tree_id']));
      if ($is_submenu) {
        // If this is a submenu, the wrapper will be handled in our override of
        // theme_menu_link, so only output the tree itself here.
        $variables['uswds_menu_tree_only'] = TRUE;
        $variables['uswds_menu_attributes']['id'] = $variables['#tree']['#uswds_menu_tree_id'];
        $variables['uswds_menu_attributes']['class'][] = 'usa-sidenav-sub_list';
      }
      else {
        $variables['uswds_menu_attributes']['class'][] = 'usa-sidenav-list';
        $variables['uswds_menu_attributes']['class'][] = 'usa-accordion';
        $variables['uswds_menu_attributes']['aria-multiselectable'] = "true";
      }
      break;

    // Footer navigation tweaks.
    case USWDS_MENU_REGION_FOOTER:
      $variables['uswds_menu_attributes']['class'][] = 'usa-unstyled-list';
      break;
  }
}

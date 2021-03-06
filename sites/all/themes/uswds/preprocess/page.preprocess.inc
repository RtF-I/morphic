<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_page().
 */
function uswds_preprocess_page(&$variables) {
  // Set the path to the base theme.
  $variables['active_theme_path'] = base_path() . drupal_get_path('theme', $GLOBALS['theme']);

  // Provide the agency information for the footer.
  $variables['display_footer_agency'] = theme_get_setting('uswds_footer_agency');
  $footer_variables = array(
    'footer_agency_name',
    'footer_agency_url',
    'footer_agency_logo',
    'contact_center',
    'phone',
    'email',
    'facebook',
    'twitter',
    'youtube',
    'rss',
  );
  foreach ($footer_variables as $footer_variable) {
    $variables[$footer_variable] = theme_get_setting('uswds_' . $footer_variable);
  }
  // Fix the footer logo path.
  if ($variables['footer_agency_logo']) {
    $variables['footer_agency_logo'] = base_path() . uswds_theme_trail_file($variables['footer_agency_logo']);
  }
  // Turn email into a mailto link.
  if ($variables['email']) {
    $variables['email'] = '<a href="mailto:' . $variables['email'] . '">' . $variables['email'] . '</a>';
  }
  // Turn phone into a tel link.
  if ($variables['phone']) {
    $variables['phone'] = '<a href="tel:' . $variables['phone'] . '">' . $variables['phone'] . '</a>';
  }

  // Decide what width the content area should have.
  $sidebar_first = (!empty($variables['page']['sidebar_first']));
  $sidebar_second = (!empty($variables['page']['sidebar_second']));
  if ($sidebar_first && $sidebar_second) {
    $variables['content_class'] = 'usa-width-one-half';
  }
  elseif ($sidebar_first || $sidebar_second) {
    $variables['content_class'] = 'usa-width-three-fourths';
  }
  else {
    $variables['content_class'] = 'usa-width-full';
  }

  // Decide on the type of header.
  $variables['header_style'] = 'usa-header-' . theme_get_setting('uswds_header_style');
  $variables['header_classes'] = 'usa-header ' . $variables['header_style'];
  if (theme_get_setting('uswds_header_mega')) {
    $variables['header_classes'] .= ' ' . $variables['header_style'] . '-megamenu';
  }
  $variables['government_banner'] = FALSE;
  if (theme_get_setting('uswds_government_banner')) {
    $variables['government_banner'] = array(
      '#theme' => 'government_banner',
      '#image_base' => $variables['active_theme_path'] . '/assets/img',
    );
  }

  // And some helpful flags for the header.
  $variables['header_basic'] = ('usa-header-basic' == $variables['header_style']);
  $variables['header_extended'] = ('usa-header-extended' == $variables['header_style']);

  // Decide on the type of footer.
  $variables['footer_style'] = 'usa-footer-' . theme_get_setting('uswds_footer_style');
  $variables['footer_classes'] = 'usa-footer ' . $variables['footer_style'];
  $variables['footer_menu_width'] = '';

  // Add some helpful flags for the footer.
  $variables['footer_slim'] = ('usa-footer-slim' == $variables['footer_style']);
  $variables['footer_medium'] = ('usa-footer-medium' == $variables['footer_style']);
  $variables['footer_big'] = ('usa-footer-big' == $variables['footer_style']);
  $variables['footer_agency_heading_class'] = 'usa-footer-logo-heading';
  $variables['footer_agency_logo_class'] = 'usa-footer-logo-img';

  // Some differences for the slim footer.
  if ($variables['footer_slim']) {
    $variables['footer_agency_heading_class'] = 'usa-footer-slim-logo-heading';
    $variables['footer_agency_logo_class'] = 'usa-footer-slim-logo-img';
    if ($variables['email'] || $variables['phone']) {
      $variables['footer_menu_width'] = 'usa-width-two-thirds';
    }
  }

  // Decide on the menus by looking inside special regions.
  $uswds_menu_present = !empty($variables['page']['primary_menu']);
  $uswds_menu_present |= !empty($variables['page']['secondary_menu']);
  $uswds_menu_present |= !empty($variables['page']['mobile_menu']);
  $variables['uswds_menu_present'] = $uswds_menu_present;

  // Whether to display the primary footer section.
  $display_primary_footer = (!empty($variables['page']['footer']));
  $display_primary_footer |= (!empty($variables['page']['footer_menu']));
  $display_primary_footer |= ($variables['footer_slim'] && ($variables['email'] || $variables['phone']));
  $variables['display_footer_primary'] = $display_primary_footer;

  // Whether to display the secondary footer section.
  $display_secondary_footer = (!empty($variables['page']['footer_secondary']));
  $display_secondary_footer |= $variables['display_footer_agency'];
  $variables['display_footer_secondary'] = $display_secondary_footer;

  // Provide this variable so that additional classes can be added to the main
  // section, similar to the header and footer.
  $variables['main_classes'] = '';
}

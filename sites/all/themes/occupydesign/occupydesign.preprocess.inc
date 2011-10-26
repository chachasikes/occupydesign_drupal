<?php
/**
 * Stub functions, orginally taken from Fusion Core.
 */

/**
 * HTML preprocessing
 */
function occupydesign_preprocess_html(&$vars) {
  global $theme_key, $user;

  // Add to array of helpful body classes
  if (isset($vars['node'])) {
    $vars['classes_array'][] = ($vars['node']) ? 'full-node' : '';                                            // Full node
    $vars['classes_array'][] = (($vars['node']->type == 'forum') || (arg(0) == 'forum')) ? 'forum' : '';      // Forum page
  }
  else {
    $vars['classes_array'][] = (arg(0) == 'forum') ? 'forum' : '';                                            // Forum page
  }

  // Add a unique page id
  $vars['body_id'] = 'pid-' . strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', drupal_get_path_alias($_GET['q'])));
}

/**
 * Maintenance page preprocessing
 */
function  occupydesign_preprocess_maintenance_page(&$vars) {
  if (class_exists('Database', FALSE)) {
    occupydesign_preprocess_html($vars);  // set html vars (html.tpl.php is in maintenance-page.tpl.php)
    occupydesign_preprocess_page($vars);  // set page vars
  }
}

/**
 * Page preprocessing
 */
function occupydesign_preprocess_page(&$vars) {

  //$fbconnect = theme_fbconnect_login_button($vars);
  //dpm($fbconnect);

  // Create variables from theme settings (set in .info file)
  $vars['sitename'] = theme_get_setting('sitename');
  
  $vars['site_slogan'] = '<h3>' . theme_get_setting('site_slogan') .'</h3>';
  if(empty($vars['site_slogan'])) {
    $vars['site_slogan'] = '<h3>' . variable_get('site_slogan') .'</h3>';
  }
  
  $vars['logo_image_link'] = theme_get_setting('logo_image_link');
  $vars['logo'] = '<a href="/"><img src="/' . drupal_get_path('theme', 'occupydesign') . '/' . $vars['logo_image_link'] . '" /></a>';
 
  $vars['prealpha'] = '';

  // If sidebars are empty, make main region full width.
  if(count($vars['page']['sidebar_first']) == 0 && count($vars['page']['sidebar_second']) == 0) {
    $vars['main_region_width'] = 'grid_16';
  }
  else {
    $vars['main_region_width'] = 'grid_11';
  }

  // Create login link
  $account_text = t('Sign in');
  global $user;
  if ($user->uid > 0) {
    // User is logged in
    $account_text = t('My Account');
  }
  $vars['account_link'] = l($account_text, 'user', array(
    'attributes' => array(
      'id' => 'signin',
    )
  ));
  
  // Temp for wireframing or MVP
  $vars['submit_btn'] = url(drupal_get_path('theme', 'occupydesign') . '/images/submit-large-overlay.gif');
  
  // Hardcoded site names
  switch ($_SERVER['HTTP_HOST']) {
    case 'staging.citygroups.org':
      $vars['sub_site_name'] = t('Staging');
      break;
      
    default:
      $vars['sub_site_name'] = t('Development');
      break;
  }

  // Remove breadcrumbs if disabled
  if (theme_get_setting('breadcrumb_display') == 0) {
    $vars['breadcrumb'] = '';
  }

/*   $vars['page_path'] = isset($_GET['q']) ? $_GET['q'] : '<front>'; */
  
  // @TODO Temp declaration of section here to prevent some bugs.
  if(empty($vars['section'])) {
    $vars['section'] = array();
    $vars['section']['section_name'] = '';
  }
  // Create variables from theme settings (set in .info file)
  if(empty($vars['sitename'])) {
    $vars['sitename'] = theme_get_setting('sitename');
  }
  if(empty($vars['site_slogan'])) {
    $vars['site_slogan'] = theme_get_setting('site_slogan');
  // Completely override slogan with count of number of groups.
  //$vars['site_slogan'] = citygroups_slogan_count();
  }

  if(empty($vars['logo'])) {
    $vars['logo_image_link'] = theme_get_setting('logo_image_link');
    $vars['logo'] = '<a href="/"><img src="/' . drupal_get_path('theme', 'citygroups') . '/' . $vars['logo_image_link'] . '" /></a>';
  }
  
}


/**
 * Region preprocessing
 */
function occupydesign_preprocess_region(&$vars) {
  // Set region variables
  $vars['region_style'] = $vars['fluid_width'] = '';
  $vars['region_name'] = str_replace('_', '-', $vars['region']);
  $vars['classes_array'][] = $vars['region_name'];
}


/**
 * Block preprocessing
 */
function occupydesign_preprocess_block(&$vars) {
  global $theme_info, $user;

  // Exit if block is outside a defined region
  if (!in_array($vars['block']->region, array_keys($theme_info->info['regions']))) {
    return;
  }
}


/**
 * Node preprocessing
 */
function occupydesign_preprocess_node(&$vars) {

  // dpm($vars); not working, use this krumo call instead to see the node object.
  var_dump(krumo($vars));

  // Add to array of handy node classes
  $vars['classes_array'][] = $vars['zebra'];                              // Node is odd or even
  $vars['classes_array'][] = (!$vars['teaser']) ? 'full-node' : '';       // Node is teaser or full-node
  
  // Add preprocess functions for all node types.
  $function = __FUNCTION__ . '_' . $vars['node']->type;
  if (function_exists($function)) {
    $function($vars);
  }

/*
  // Node top, bottom & sidebar can't be set with context, unfortunately, until we can figure out
  // how to access blocks set by context. Context seems to override the entire block system...
  // So for now, node regions should only be set in preprocessing
  // functions - to be used for certain fields and the like.*/

  $vars['node_top'] = '';
  $vars['node_bottom'] = '';
  $vars['node_sidebar'] = '';

}

/**
 * Comment preprocessing
 */
function occupydesign_preprocess_comment(&$vars) {
  static $comment_odd = TRUE;
 // Comment is odd or even

  // Add to array of handy comment classes
  $vars['classes_array'][] = $comment_odd ? 'odd' : 'even';
  $comment_odd = !$comment_odd;
}


/**
 * Preprocessing function for node types.
 */
function occupydesign_preprocess_node_symbol(&$vars) {

/*
  $field = $vars['field_image_references'];

  foreach($field as $key => $value) {
    $image_path = $vars['field_image_references'][$key]['und']['url'];
    
    if(substr($image_path, 0, 21) == 'http://www.flickr.com') {
      // is flickr
      if(substr($image_path, -1, 3) !== 'jpg') {
        $image_path = $image_path . 'sizes/l/in/photostream/';      
      }

    }
    
  }
  
  $vars['loaded_images'] = '<img src="' . $image_path . '" />';
*/
}

<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html class="no-js" xmlns:fb="http://www.facebook.com/2008/fbml" 
                    xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" 
                    lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">


<head profile="<?php print $grddl_profile; ?>">
  <meta charset="utf-8">
  <!-- Always force latest IE rendering engine (even in intranet) & Chrome Frame
       Remove this if you use the .htaccess -->
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

  <?php print $head; ?>
  <title><?php print $head_title; ?></title>

  <!-- Mobile viewport optimized: j.mp/bplateviewport -->
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <?php print $styles; ?>
  <?php print $scripts; ?>

  <?php global $base_url; ?>
  <base href="<?php  print $base_url ?>" />

<link href="http://fonts.googleapis.com/css?family=Oswald" rel="stylesheet" type="text/css">

<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="distribution" content="global">
<meta name="robots" content="follow, all">
<meta name="language" content="en">
<meta name="verify-v1" content="7XvBEj6Tw9dyXjHST/9sgRGxGymxFdHIZsM6Ob/xo5E=">
<meta name="description" content="Building a visual language for the 99%, grassroots style. Infographic + other protest signs, logistical signage, and universal icons to support the Occupy Together movement.">


<title> OccupyDesign</title>
<link rel="Shortcut Icon" href="http://occupydesign.org/wp-content/themes/organic_structure_white/images/favicon.ico" type="image/x-icon">

<link rel="stylesheet" href="http://occupydesign.org/wp-content/themes/organic_structure_white/style.css" type="text/css" media="screen">
<link rel="alternate" type="application/rss+xml" title="OccupyDesign RSS Feed" href="http://occupydesign.org/feed/">
<link rel="alternate" type="application/atom+xml" title="OccupyDesign Atom Feed" href="http://occupydesign.org/feed/atom/">
<link rel="pingback" href="http://occupydesign.org/xmlrpc.php">


  <!-- Uncomment if you are specifically targeting less enabled mobile browsers
  <link rel="stylesheet" media="handheld" href="css/handheld.css?v=2">  -->
</head>
<body id="<?php print $body_id; ?>" class="<?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>

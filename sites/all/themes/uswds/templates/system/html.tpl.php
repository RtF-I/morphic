<!DOCTYPE html>
<html <?php print $rdf_namespaces; ?>>

  <head>
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>

    <!-- Basic Page Needs -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <!-- Mobile Specific Metas -->
    <meta name="HandheldFriendly" content="True">
    <meta name="MobileOptimized" content="320">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <!-- Favicons -->
    <!-- 128x128 -->
    <link rel="icon" type="image/png" href="<?php print $favicon_path; ?>favicon.png" />
    <!-- 192x192, as recommended for Android http://updates.html5rocks.com/2014/11/Support-for-theme-color-in-Chrome-39-for-Android -->
    <link rel="icon" type="image/png" sizes="192x192" href="<?php print $favicon_path; ?>favicon-192.png" />
    <!-- 57x57 (precomposed) for iPhone 3GS, pre-2011 iPod Touch and older Android devices -->
    <link rel="apple-touch-icon-precomposed" href="<?php print $favicon_path; ?>favicon-57.png">
    <!-- 72x72 (precomposed) for 1st generation iPad, iPad 2 and iPad mini -->
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="<?php print $favicon_path; ?>favicon-72.png">
    <!-- 114x114 (precomposed) for iPhone 4, 4S, 5 and post-2011 iPod Touch -->
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="<?php print $favicon_path; ?>favicon-114.png">
    <!-- 144x144 (precomposed) for iPad 3rd and 4th generation -->
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="<?php print $favicon_path; ?>favicon-144.png">

    <?php print $styles; ?>
  </head>

  <body class="<?php print $classes; ?>" <?php print $attributes;?>>
    <a class="usa-skipnav" href="#main-content"><?php print t('Skip to main content'); ?></a>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $scripts; ?>
    <?php print $page_bottom; ?>
  </body>

</html>

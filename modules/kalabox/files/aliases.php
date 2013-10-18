<?php

/**
 * @file
 * Print all our sites as JSON.
 */

/**
 * Converts a raw alias to a JSON-friendly, trimmed down version.
 *
 * @param string $name
 *   Name of the alias.
 * @param array $alias
 *   Entire alias array from Drush.
 *
 * @return array
 *   Optimized alias array.
 */
function convertAlias($name, $alias) {
  $converted = array(
    'aliasName' => $name,
    'webRoot' => $alias['root'],
    'uri' => $alias['uri']
  );
  if (isset($alias['built-from'])) {
    $converted['builtFrom'] = $alias['built-from'];
  }
  if (isset($alias['read-name'])) {
    $converted['name'] = $alias['read-name'];
  }
  if (isset($alias['thumbnail'])) {
    $converted['imgSrc'] = 'http://root.kala/.images/' . $alias['read-name'] . '.png';
  }
  return $converted;
}

$site_aliases = array(
  'builtSites' => array(),
  'unbuiltSites' => array(),
);

// Load aliases of built sites.
$aliases = array();
if (file_exists('/etc/drush/kalastack.aliases.drushrc.php')) {
  include '/etc/drush/kalastack.aliases.drushrc.php';
}
$built_sites = $aliases;
foreach ($built_sites as $name => $built_site) {
  $site_aliases['builtSites'][] = convertAlias($name, $built_site);
}

// Load aliases of remote sites.
$aliases = array();
if (file_exists('/etc/drush/pantheon.aliases.drushrc.php')) {
  include '/etc/drush/pantheon.aliases.drushrc.php';
}
$remote_sites = $aliases;

// Find remote sites that haven't been built yet, skipping non-dev sites.
foreach ($remote_sites as $site_name => $remote_site) {
  if (strpos($site_name, '.dev') === FALSE) {
    continue;
  }
  $site_built = FALSE;
  foreach ($site_aliases['builtSites'] as $built_site) {
    if (isset($built_site['builtFrom']) && $built_site['builtFrom'] == $site_name) {
      $site_built = TRUE;
    }
  }
  if (!$site_built) {
    $site_aliases['unbuiltSites'][] = convertAlias($site_name, $remote_site);
  }
}

// Return sites lists as JSON.
echo json_encode($site_aliases);

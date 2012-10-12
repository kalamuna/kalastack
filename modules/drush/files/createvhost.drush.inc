<?php

/**
 * @file
 *   createvhost.drush.inc
 * 
 */


/**
 * Implementation of hook_drush_command().
 * 
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function createvhost_drush_command() {
  $items = array();

  // the key in the $items array is the name of the command.
  $items['createvhost'] = array(
    // the name of the function implementing your command.
    'callback' => 'createvhost_vhost',
    // a short description of your command
    'description' => dt('Build a basic drupal nginx vhost.'),
    'arguments' => array(
       'site' => dt('The drupal sub-site to enable. e.g. www.yoursite.net. Only works when a drupal install is enabled.'),
    ),
  );
  
  return $items;
}


/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function createvhost_drush_help($section) {
  switch ($section) {
  case 'drush:createvhost':
    return dt("Build a basic drupal nginx vhost");
  }
}


/** 
 *
 * @param
 *   string $site the site to create
 * @return
 *   void all error handling is being done in densite_exec
 */
function createvhost_vhost($site){
  // create the log files
  # drush_shell_exec("mkdir /var/www/" . $site);
  
  // search and replace in apache configuration
  drush_shell_exec("sudo cp /etc/nginx/sites-available/drupaldefault /tmp/" . $site);
  $vhost_default_string = createvhost_get_file("/tmp/" . $site);
  $search = array("drupal.kala", "/var/www/drupal", "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS");
  $replace = array($site . ".kala", "/var/www/" . $site, "");
  $vhost_default_string = str_replace($search, $replace, $vhost_default_string);

  // write the file 
  createvhost_write_file("/tmp/" . $site, $vhost_default_string);
  drush_shell_exec ("sudo cp /tmp/" . $site . " /etc/nginx/sites-available/" . $site);
  drush_shell_exec ("sudo ln -s /etc/nginx/sites-available/" . $site . " /etc/nginx/sites-enabled/" . $site);

  // reload apache
  drush_shell_exec ("sudo service nginx restart");
  createvhost_update_etc_hosts($site . ".kala");
}



/**
 * @param 
 *  string $filename The filename to open and read
 * @return 
 *  string $content of the file which has been read 
*/
function createvhost_get_file($filename){
  clearstatcache();
  $content = fread($fp = fopen($filename, 'r'), max(1, filesize($filename))); 
  fclose($fp);
  return $content;
}


/**
 * @param
 *  string $filename The filename to write
 * @param
 *  string $contents the content to write
 */
function createvhost_write_file($filename, $contents) {
  if ($fp = @fopen($filename, 'w')) {
    flock($fp,2);
    fwrite($fp, $contents);
    flock($fp,3);
    fclose($fp);
    return 1;
  } else {
    return 0;
  }
}

function createvhost_update_etc_hosts($hostname){
    // create new hosts file and reload server
    $hosts_file_str = file_get_contents("/etc/hosts");
    $new_host = "127.0.0.1\t$hostname\n";
    if (!strstr($hosts_file_str, $new_host)) {
      $new_hosts_file_str =  $new_host . $hosts_file_str;
      file_put_contents("/tmp/hosts", $new_hosts_file_str);
      drush_shell_exec("sudo cp -f /tmp/hosts /etc/hosts");
      drush_shell_exec("sudo service nginx restart");
      drush_shell_exec("rm /tmp/hosts");
    }
}
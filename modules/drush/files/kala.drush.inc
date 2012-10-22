<?php

/**
 * @file
 *   kala.drush.inc
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
function kala_drush_command() {
  $items = array();
  
  $items['kala'] = array(
    'callback' => 'kala_kala',
    'description' => dt('Shows some useful information for your kalabox'),
    'aliases' => array('ks'),
    'examples' => array(
      'drush kala' => 'Shows some useful information for your kalabox',
     ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalavhost'] = array(
    'callback' => 'kala_vhost',
    'description' => dt('Builds a basic Drupal nginx vhost. Must use valid Pantheon alias as first argument.'),
    'aliases' => array('vhost', 'kvh'),
    'examples' => array(
      'drush kvh pantheon.sitename.dev' => 'Builds a nginx vhost with info from pantheon.sitename.dev at sitename.kala',
     ),
     'arguments' => array(
       'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
     ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalacode'] = array(
    'callback' => 'kala_code',
    'description' => dt('Git clones your Pantheon site codebase'),
    'aliases' => array('code', 'kc'),
    'examples' => array(
      'drush code pantheon.sitename.dev' => 'Git clone of your pantheon site. Must use valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kaladata'] = array(
    'callback' => 'kala_data',
    'description' => dt('Imports your Pantheon site database'),
    'aliases' => array('data', 'kd'),
    'examples' => array(
      'drush data pantheon.sitename.dev' => 'Import the DB of your pantheon site. Must use valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalafiles'] = array(
    'callback' => 'kala_files',
    'description' => dt('Imports your Pantheon site files'),
    'aliases' => array('files', 'kf'),
    'examples' => array(
      'drush files pantheon.sitename.dev' => 'Imports the files of your pantheon site. Must use valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalabuild'] = array(
    'callback' => 'kala_build',
    'description' => dt('Imports your Pantheon site'),
    'aliases' => array('build', 'kb'),
    'examples' => array(
      'drush build pantheon.sitename.dev' => 'Imports the code, data and files of your pantheon site. Must use valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalarefresh'] = array(
    'callback' => 'kala_build',
    'description' => dt('Refreses your Pantheon site'),
    'aliases' => array('krefresh', 'kr'),
    'examples' => array(
      'drush kr pantheon.sitename.dev' => 'Refreshes the code, data and files of your pantheon site. Must use valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kaladestroy'] = array(
  	'callback' => 'kala_destroy',
  	'description' => dt('Removes a pantheon site'),
  	'aliases' => array('destroy', 'crush', 'wmb', 'kd'),
  	'examples' => array(
  	  'drush crush pantheon.sitename.dev' => 'Deletes the Pantheon site. Must use valid Pantheon alias as first argument.',
     ),
  	'arguments' => array(
      'site' => 'A valid Pantheon site alias. Do not use the @ convention for this alias as we are not using it as our site.',
  	),
  	'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
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
function kala_drush_help($section) {
  switch ($section) {
    case 'drush:kala':
      return dt("Shows useful info.");
    case 'drush:kalavhost':
      return dt("Build a basic drupal nginx vhost.");
    case 'drush:kalacode':
      return dt("Gets Pantheon codebase.");
    case 'drush:kaladata':
      return dt("Gets Pantheon database.");
    case 'drush:kalafiles':
      return dt("Gets Pantheon files.");
    case 'drush:kalabuild':
      return dt("Builds your Pantheon site.");
    case 'drush:kalabuild':
      return dt("Refreshes your Pantheon site.");
  }
}


/** 
 *
 */
function kala_vhost(){
  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  
  $site = $pantheon['site'];
    
  if ($pantheon != FALSE) {
    if (!file_exists("/etc/nginx/sites-available/" . $site)) {
      if (is_dir("/var/www/" . $site)) {
        drush_shell_exec("cp /etc/nginx/sites-available/drupaldefault /tmp/" . $site);
        $vhost_default_string = kala_get_file("/tmp/" . $site);
        
        $search = array("drupal.kala", "/var/www/drupal", "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS");
        $replace = array($site . ".kala", "/var/www/" . $site, "");
        $vhost_default_string = str_replace($search, $replace, $vhost_default_string);
        
        
        kala_write_file("/tmp/" . $site, $vhost_default_string);
        drush_shell_exec ("cp /tmp/" . $site . " /etc/nginx/sites-available/" . $site);
        drush_shell_exec ("ln -s /etc/nginx/sites-available/" . $site . " /etc/nginx/sites-enabled/" . $site);
      
        drush_shell_exec ("service nginx restart");
        kala_update_etc_hosts($site . ".kala");
      }
    }
    else {
      drush_log('vhost file already exists', 'warning');
    }
  }
  else {
    return;
  }
}

/** 
 *
 */
function kala_kala(){
  drush_print("
  Useful Locations
  =====================
  Home/phpinfo()            - http://kala
  phpMyAdmin                - http://php.kala
  solr                      - http://kala:8080/solr
  drush                     - /usr/share/drush
  SSH public key            - ~/.ssh/id_rsa.pub
  Pantheon aliases          - ~/.drush/pantheon.aliases.drushrc.php

  Useful Commands
  =====================
  Generate new SSH key      - ssh-keygen
  Display SSH public key    - cat ~/.ssh/id_rsa.pub

  FOR PANTHEON
  Show info                 - drush kala
      
  Get/refresh code          - drush code pantheon.SITENAME.dev
  Get/refresh database      - drush data pantheon.SITENAME.dev
  Get/refresh files         - drush files pantheon.SITENAME.dev
  
  Build entire site         - drush build pantheon.SITENAME.dev
  Refresh entire site       - drush krefresh pantheon.SITENAME.dev
  Destroy entire site       - drush crush pantheon.SITENAME.dev
  
  ");
}

/**
 *
 */
function kala_code(){
  
  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  
  if ($pantheon != FALSE) {
    drush_print_table(drush_key_value_to_array_table($pantheon));
    drush_log('pantheon environment and database variables loaded', 'success');
    
    drush_print('checking if a local codebase already exists');
    if (is_dir("/var/www/" . $pantheon['site'])) {
      if (drush_shell_exec("cat /var/www/" . $pantheon['site'] . "/.git/config | grep url")) {
        drush_log('you may have already downloaded this codebase!', 'warning');
        
        drush_shell_exec("cat /var/www/" . $pantheon['site'] . "/.git/config | grep url > /tmp/gitconfig" . $pantheon['site']);
        $gitconfig_string = trim(file_get_contents("/tmp/gitconfig" . $pantheon['site']));
        drush_shell_exec("rm /tmp/gitconfig" . $pantheon['site']);
        
        if ($gitconfig_string == "url = git@code.getpantheon.com:" . $pantheon['id']) {
          drush_log('silly you! you have already downloaded this codebase... refreshing code', 'warning');
          drush_shell_exec("git --git-dir=/var/www/" . $pantheon['site']. "/.git pull");
          drush_log('code refreshed!', 'success');
        }
        else {
          drush_log('directory /var/www/' . $pantheon['site'] . ' exists is not empty, is a codebase, but not the right one. please remove this directory before you attempt to download your codebase.', 'error');
        }
      }
      else {
        drush_log('directory /var/www/' . $pantheon['site'] . ' exists is not empty and is not your codebase. please remove this directory before you attempt to download your codebase.', 'error');
      }
    }
    else {
      drush_print('no local codebase, attempting a git clone, this may take a few minutes so please be patient...');
      if (drush_shell_exec("git clone git@code.getpantheon.com:" . $pantheon['id'] . " /var/www/" . $pantheon['site'])) {
        drush_log('all your pantheon codebase are belongs to you!', 'success');
      }
      else {
        drush_log('could not git clone, check to see the directory /var/www/' . $pantheon['site'] . ' is empty and your ssh keys are installed correctly', 'error');
      }
    }
  }
  else {
    return;
  }
}

/**
 *
 */
function kala_data(){
  
  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  $pantheon['kaladb']  = str_replace("-", "_", $pantheon['site'] . "_kala");
  
  if ($pantheon != FALSE) {

    drush_print_table(drush_key_value_to_array_table($pantheon));
    drush_log('pantheon environment and database variables loaded', 'success');

    drush_print('attempting a database download, this may take a few minutes so please be patient...');
    
    if (drush_shell_exec("mysqldump -u" . $pantheon['database_user'] . " -hdbserver." . $pantheon['env'] ."." . $pantheon['id'] .".drush.in -P" . $pantheon['database_port'] ." -p" . $pantheon['database_password'] . " --opt " . $pantheon['database_database'] ." > /tmp/" . $pantheon['id'] .".sql")) {    
      drush_log('data downloaded from pantheon', 'success');
    }
    else {
      drush_log('could not get data from pantheon', 'error');
    }
    
    if (drush_shell_exec("mysql -uroot -ppassword -hkala -e \"create database " . $pantheon['kaladb'] . "\"")) {
      drush_log('new local database ' . $pantheon['kaladb'] . ' created', 'success');
    }
    else {
      drush_log('database already exists, skipping', 'notice');
    }
    
    if (drush_shell_exec("mysql -uroot -ppassword -hkala " . $pantheon['kaladb'] . " < /tmp/" . $pantheon['id'] .".sql")) {
      drush_log('your pantheon data has been imported to ' . $pantheon['kaladb'], 'success');
    }
    else {
      drush_log('pantheon data unable to be imported', 'error');
    }
    
    drush_shell_exec("rm /tmp/" . $pantheon['id'] .".sql");
  }
  else {
    return;
  }
}

/**
 *
 */
function kala_files(){

  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  if ($pantheon != FALSE) {

    drush_print_table(drush_key_value_to_array_table($pantheon));
    drush_log('pantheon environment and database variables loaded', 'success');
    
    drush_print('checking to see if you already have synced files');
    if (is_dir("/var/www/" . $pantheon['site'] . "/sites/default/files")) {
      drush_log('you have!', 'success');
    }
    else {
      mkdir("/var/www/" . $pantheon['site'] . "/sites/default/files");     
      drush_log('files directory created', 'success');
      drush_shell_exec("chmod 775 /var/www/" . $pantheon['site'] . "/sites/default/files");
    }
    
    drush_log('starting files sync, this may take a few minutes...', 'success');
    drush_shell_exec("rsync -rlztv --ipv4 -e 'ssh -p 2222' --exclude 'js' --exclude 'css' --exclude 'ctools' --exclude 'imagecache' --exclude 'xmlsitemap' --exclude 'backup_migrate' --exclude 'styles' " . $pantheon['env'] . "." . $pantheon['id'] . "@appserver." . $pantheon['env'] . "." . $pantheon['id'] . ".drush.in:code/sites/default/files/. /var/www/" . $pantheon['site'] . "/sites/default/files");
    drush_log('files synced!', 'success');

  }
  else {
    return;
  }
}

/**
 *
 */
function kala_build(){
  
  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  if ($pantheon != FALSE) {
    
    drush_print('preparing to build your pantheon site... this might take awhile');
    
    kala_code($args[0]);
    drush_log('Codebase: Success!', 'success');
    
    kala_data($args[0]);
    drush_log('Database: Success!', 'success');
    
    kala_files($args[0]);
    drush_log('Files: Success!', 'success');
    
    _kala_reset_settings($pantheon);
    drush_log('Settings: Rebuilt!, check git status', 'success');
    
    drush_shell_exec("sudo drush vhost " . $args[0]);
    
    drush_log('Build: Success!', 'success');

  }
  else {
    return;
  }
}

/**
 *
 */
function kala_destroy(){

  $args = func_get_args();
  $pantheon = _kala_get_pantheon($args[0]);
  $pantheon['kaladb']  = str_replace("-", "_", $pantheon['site'] . "_kala");
  
  if ($pantheon != FALSE) {

    drush_print('preparing to crush your pantheon site... this might take awhile');

	if (drush_shell_exec("sudo rm -rf /var/www/" . $pantheon['site'])) {
	  drush_log('code and files crushed', 'success');
	}
	if (drush_shell_exec("mysql -uroot -ppassword -hkala -e \"drop database " . $pantheon['kaladb'] . "\"")) {
	  drush_log('database crushed', 'success');
	}
	
	if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-available/" . $pantheon['site'])) {
	  if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-enabled/" . $pantheon['site'])) {
	  	drush_log('vhosts removed', 'success');
	  }
	} 
	
	if (drush_shell_exec("sudo service nginx restart")) {
	  drush_log('nginx restart', 'success');
	}
	
	kala_remove_etc_hosts($pantheon['site'] . ".kala");

	drush_log('site destroyed', 'success');
	
  }
  else {
    return;
  }
}

/**
 * @param 
 *  string $filename The filename to open and read
 * @return 
 *  string $content of the file which has been read 
*/
function kala_get_file($filename){
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
function kala_write_file($filename, $contents) {
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

function kala_update_etc_hosts($hostname) {
    // create new hosts file and reload server
    $hosts_file_str = file_get_contents("/etc/hosts");
    $new_host = "127.0.0.1\t$hostname\n";
    if (!strstr($hosts_file_str, $new_host)) {
      $new_hosts_file_str =  $new_host . $hosts_file_str;
      file_put_contents("/tmp/hosts", $new_hosts_file_str);
      drush_shell_exec("sudo cp -f /tmp/hosts /etc/hosts");
      #drush_shell_exec("sudo service nginx restart");
      drush_shell_exec("rm /tmp/hosts");
    }
}

function kala_remove_etc_hosts($hostname) {
  // create new hosts file and reload server
  drush_shell_exec("sed /" . $hostname . ".kala/d /etc/hosts > /tmp/hosts");
  drush_shell_exec("sudo cp -f /tmp/hosts /etc/hosts");
  drush_shell_exec("rm /tmp/hosts");
}


/**
 * Check for valid pantheon alias
 */
function _kala_get_pantheon($sitename) {
  // load all available aliases
  drush_sitealias_load_all();
  $aliases = drush_get_context('site-aliases');
  
  if (isset($aliases['@' . $sitename])) {
    $site = explode('.', $aliases['@' . $sitename]['uri']);
    $user = explode('.', $aliases['@' . $sitename]['remote-user']);
    
    // weak check if alias is valid pantheon alias
    if ($site[0] != 'dev') {
      drush_log('we do not allow access to the live or test sites', 'error');
      return FALSE;
    }
    elseif ($site[2] != 'gotpantheon' || !isset($aliases['@' . $sitename]['remote-host']) || !isset($aliases['@' . $sitename]['remote-user']) || !isset($aliases['@' . $sitename]['ssh-options'])) {
      drush_log('not a validly formatted pantheon alias', 'error');
      return FALSE;
    }
    else {
      drush_log('valid pantheon alias located', 'success');
      $pantheon = array();
    
      // load environment
      $pantheon['env'] = $site[0];
      $pantheon['site'] = $site[1];
      $pantheon['id'] = $user[1];
      $pantheon['ssh'] = $aliases['@' . $sitename]['ssh-options'];
      
      // load database
      // get connect string, dump it into file, load it into php
      drush_shell_exec("ssh " . $pantheon['ssh'] . " '" . $pantheon['env'] . "." . $pantheon['id'] . "'@'appserver." . $pantheon['env'] . "." . $pantheon['id'] . ".drush.in' 'drush  --root='\''.'\'' --uri='\''" . $pantheon['env'] . "." . $pantheon['site'] .".gotpantheon.com'\'' sql-connect' > /tmp/" . $pantheon['id']);
      $db_string = file_get_contents("/tmp/" . $pantheon['id']);
      drush_shell_exec("rm /tmp/" . $pantheon['id']);
      
      // parse connection string
      $db_array = explode("--", $db_string);
      array_shift($db_array);
      
      foreach ($db_array as $row) {
        $keyvalue = explode("=", $row);
        $pantheon['database_' . trim($keyvalue[0])] = trim($keyvalue[1]);
        unset($keyvalue);
      }
            
      return $pantheon;
    }
  }
  else {
    drush_log('pantheon alias does not exist, please make sure you have a recent copy of all your aliases', 'error');
  }
}


/**
 * rebuild settings.php with kala settings
 */
function _kala_reset_settings($pantheon) {
  require_once("/var/www/" . $pantheon['site'] . "/sites/default/settings.php");
  $pantheon['kaladb']  = str_replace("-", "_", $pantheon['site'] . "_kala");
  
  if (isset($db_url)) {
  	if (strpos($db_url, $pantheon['kaladb']) === FALSE) { 
	  $settingsfile = "/var/www/" . $pantheon['site'] . "/sites/default/settings.php";
	  $fh = fopen($settingsfile, 'a') or die("can't open file");
	  $settings =
	  '
	  /**
	   * Kalabox local settings
	   */
	   
	  $db_url = \'mysql://root:password@kala/' . $pantheon['kaladb'] . '\';';
	  
	  fwrite($fh, $settings);
	  fclose($fh);
  	}
  }
  else {
    if ($databases['default']['default']['database'] != $pantheon['kaladb'] ) {
      
      // haven't decided if we should enforce this or an autocommit or what
      // drush_shell_exec("git --git-dir=/var/www/" . $pantheon['site'] . "/.git update-index --assume-unchanged /var/www/" . $pantheon['site'] . "/sites/default/settings.php");
      
      $settingsfile = "/var/www/" . $pantheon['site'] . "/sites/default/settings.php";
      $fh = fopen($settingsfile, 'a') or die("can't open file");
      $settings =
      '
      /**
      * Kalabox local settings
      */
       
      $databases[\'default\'][\'default\'] = array(
      \'driver\' => \'mysql\',
      \'database\' => \'' . $pantheon['kaladb'] . '\',
      \'username\' => \'root\',
      \'password\' => \'password\',
      \'host\' => \'kala\',
      \'prefix\' => \'\',
      );
    
      ';
      fwrite($fh, $settings);
      fclose($fh);
    }
  }
}
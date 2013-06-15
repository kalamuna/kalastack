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
    
  if ($pantheon !== FALSE) {
  	$site = $pantheon['site'];
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
      drush_log('Seriously, the vhost file already exists!', 'warning');
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
  
  if ($pantheon !== FALSE) {    
    drush_print('Coder, do you already have a local codebase for this site?');
    if (is_dir("/var/www/" . $pantheon['site'])) {
      if (drush_shell_exec("cat /var/www/" . $pantheon['site'] . "/.git/config | grep url")) {
        drush_log('It looks like you might!', 'warning');
        
        drush_shell_exec("cat /var/www/" . $pantheon['site'] . "/.git/config | grep url > /tmp/gitconfig" . $pantheon['site']);
        $gitconfig_string = trim(file_get_contents("/tmp/gitconfig" . $pantheon['site']));
        drush_shell_exec("rm /tmp/gitconfig" . $pantheon['site']);
        
        if ($gitconfig_string == "url = ssh://codeserver.dev." . $pantheon['id'] . "@codeserver.dev." . $pantheon['id'] . ".drush.in:2222/~/repository.git") {
          drush_log('Oh you! You have already downloaded this code. I guess we will just refresh it then.', 'warning');
          drush_shell_exec("git --git-dir=/var/www/" . $pantheon['site']. "/.git pull");
          drush_log('And... we refreshed that stale stale code!', 'success');
        }
        else {
          drush_log('Directory /var/www/' . $pantheon['site'] . ' exists... and is not empty... and is a codebase but not the right codebase. Please remove this directory before you attempt to download your codebase. Chump!', 'error');
        }
      }
      else {
        drush_log('Directory /var/www/' . $pantheon['site'] . ' exists... and is not empty... and is not a codebase. Please remove this directory before you attempt to download your codebase. You vicious knave you!', 'error');
      }
    }
    else {
      drush_print('Coder, your code fields are fertile and unblemished. Prepare to receive a potent load of code seed. Also this may take a few minutes so please be patient...');
      // try to connect via ssh
      if (drush_shell_exec("git clone ssh://codeserver.dev." . $pantheon['id'] . "@codeserver.dev." . $pantheon['id'] . ".drush.in:2222/~/repository.git /var/www/" . $pantheon['site'])) {
          drush_log('Your code fields bloom!', 'success');
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
  
  if ($pantheon !== FALSE) {

  	$pantheon['kaladb']  = str_replace("-", "_", $pantheon['site'] . "_kala");
  	
    drush_print('Dear sir! We are now attempting a database download, please standby...');
    
    if (drush_shell_exec("mysqldump -u" . $pantheon['db_user'] . " -h" . $pantheon['db_host'] ." -P" . $pantheon['db_port'] ." -p" . $pantheon['db_pass'] . " --opt " . $pantheon['db_db'] ." > /tmp/" . $pantheon['kaladb'] .".sql")) {    
      drush_log('Indeed! Your data is now in our sweet sweet hands.', 'success');
    }
    else {
      drush_log('Bollocks! We could not retrieve your data!', 'error');
    }
    
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"create database " . $pantheon['kaladb'] . "\"")) {
      drush_log('Dearest friend, a new database called ' . $pantheon['kaladb'] . ' hath been created', 'success');
    }
    else {
      drush_log('This database already exists! What are you trying to do!!!', 'notice');
    }
    
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost " . $pantheon['kaladb'] . " < /tmp/" . $pantheon['kaladb'] .".sql")) {
      drush_log('SOMETHING SOMETHING SOMETHING IMPORT COMPLETE', 'success');
    }
    else {
      drush_log('Sadface: pantheon data unable to be imported', 'error');
    }
    
    drush_shell_exec("rm /tmp/" . $pantheon['kaladb'] .".sql");
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
  
  if ($pantheon !== FALSE) {

    drush_print('We are now in the process of checking to see whether or not you have tried to sync these here filez before!');
    if (is_dir("/var/www/" . $pantheon['site'] . "/sites/default/files")) {
      drush_log('you have!', 'success');
    }
    else {
      mkdir("/var/www/" . $pantheon['site'] . "/sites/default/files");     
      mkdir("/var/www/" . $pantheon['site'] . "/sites/default/private");
      drush_log('Building up some sweet sweet files directories for you', 'success');
      drush_shell_exec("chmod 775 /var/www/" . $pantheon['site'] . "/sites/default/files");
      drush_shell_exec("chmod 775 /var/www/" . $pantheon['site'] . "/sites/default/private");
    }
    
    drush_log('Doing that funky file sync tango. It feels good. Please wait...', 'success');
    drush_shell_exec("rsync -rlztv --ipv4 -e 'ssh -p 2222' --exclude 'js' --exclude 'css' --exclude 'ctools' --exclude 'imagecache' --exclude 'xmlsitemap' --exclude 'backup_migrate' --exclude 'styles' --exclude 'less' " . $pantheon['env'] . "." . $pantheon['id'] . "@appserver." . $pantheon['env'] . "." . $pantheon['id'] . ".drush.in:files /var/www/" . $pantheon['site'] . "/sites/default/");    
    drush_log('Consider your files N*SYNC', 'success');
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
  
  if ($pantheon !== FALSE) {
    
    drush_print('WE GONE BUILD THIS HERE SITE NOW! STANDBY LADDY/LASS');
    
    kala_code($args[0]);
    drush_log('Codebase: Q\'Plah!', 'success');
    
    kala_data($args[0]);
    drush_log('Database: Q\'Plah!', 'success');
    
    kala_files($args[0]);
    drush_log('Files: Q\'Plah!', 'success');
    
    _kala_reset_settings($pantheon);
    drush_log('Settings: Rebuilt!, Check git status', 'success');
    
    drush_shell_exec("sudo drush vhost " . $args[0]);
    
    drush_shell_exec("cd /var/www/" . $args[0]);
    drush_shell_exec("drush cc all -y");
    drush_log('Drush: We clear yo cache', 'success');
    
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
  
  if ($pantheon !== FALSE) {
  	
  	$pantheon['kaladb']  = str_replace("-", "_", $pantheon['site'] . "_kala");

    drush_print('PREPARE TO RIDE ON EL CRUSH BUS');

	if (drush_shell_exec("sudo rm -rf /var/www/" . $pantheon['site'])) {
	  drush_log('CODES/FILES = FUCKING CRUSHED', 'success');
	}
	if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"drop database " . $pantheon['kaladb'] . "\"")) {
	  drush_log('DB = FUCKING CRUSHED', 'success');
	}
	
	if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-available/" . $pantheon['site'])) {
	  if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-enabled/" . $pantheon['site'])) {
	  	drush_log('VHOST = FUCKING CRUSHED', 'success');
	  }
	} 
	
	if (drush_shell_exec("sudo service nginx restart")) {
	}
	
	kala_remove_etc_hosts($pantheon['site'] . ".kala");
	drush_log('SITE = FUCKING CRUSHED', 'success');
	
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
  drush_shell_exec("sed /" . $hostname . "/d /etc/hosts > /tmp/hosts");
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
    if ($user[0] != 'dev') {
      drush_log('WE ONLY BUILD FROM DEV YO', 'error');
      return FALSE;
    }
    elseif (!isset($aliases['@' . $sitename]['remote-host']) || !isset($aliases['@' . $sitename]['remote-user']) || !isset($aliases['@' . $sitename]['db-url'] )) {
      drush_log('Probably not a validly formatted pantheon alias', 'error');
      return FALSE;
    }
    else {
      $pantheon = array();
      
      $siteal = explode('.', $sitename);
    
      // load environment
      $pantheon['env'] = $user[0];
      $pantheon['site'] = $siteal[0];
      $pantheon['id'] = $user[1];
      $pantheon['ssh'] = $aliases['@' . $sitename]['ssh-options'];
      $pantheon['db_url'] = $aliases['@' . $sitename]['db-url'];
      
      $regex = '/^mysql:\/\/([^:]+):([^@]+)@([^:]+):(\d+)\/(.+)$/';
      $matches = array();
      preg_match($regex, $pantheon['db_url'], $matches);
      
      $pantheon['db_user'] = $matches[1];
      $pantheon['db_pass'] = $matches[2];
      $pantheon['db_host'] = $matches[3];
      $pantheon['db_port'] = $matches[4];
      $pantheon['db_db'] = $matches[5];

      return $pantheon;
    }
  }
  else {
    drush_log('Pantheon alias does not exist, please make sure you have a recent copy of all your aliases', 'error');
    return FALSE;
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
	   
	  $db_url = \'mysql://root:password@localhost/' . $pantheon['kaladb'] . '\';';
	  
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
      \'host\' => \'localhost\',
      \'prefix\' => \'\',
      );
    
      ';
      fwrite($fh, $settings);
      fclose($fh);
    }
  }
}



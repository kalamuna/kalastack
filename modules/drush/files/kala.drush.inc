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

  $items['kalavhost'] = array(
    'callback' => 'kala_vhost',
    'description' => dt('Builds a basic Drupal nginx vhost. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.'),
    'aliases' => array('vhost', 'kvh'),
    'examples' => array(
      'drush kvh sitename.dev' => 'Builds a nginx vhost with info from (pantheon).sitename.dev at sitename.kala',
     ),
     'arguments' => array(
       'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
     ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalacode'] = array(
    'callback' => 'kala_code',
    'description' => dt('Git clones your Pantheon site codebase'),
    'aliases' => array('code', 'kc'),
    'examples' => array(
      'drush code sitename.dev' => 'Git clone of your pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
    ),

    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kaladata'] = array(
    'callback' => 'kala_data',
    'description' => dt('Imports your Pantheon site database'),
    'aliases' => array('data', 'kd'),
    'examples' => array(
      'drush data sitename.dev' => 'Import the DB of your pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalafiles'] = array(
    'callback' => 'kala_files',
    'description' => dt('Imports your Pantheon site files'),
    'aliases' => array('files', 'kf'),
    'examples' => array(
      'drush files sitename.dev' => 'Imports the files of your pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kalabuild'] = array(
    'callback' => 'kala_build',
    'description' => dt('Imports your Pantheon site'),
    'aliases' => array('build', 'kb'),
    'examples' => array(
      'drush build sitename.dev' => 'Imports the code, data and files of your pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
    ),
    'options' => array(
      'profile' => array(
        'description' => 'Comma delimited list of spreads.',
        'example-value' => 'panopoly,openatrium',
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['kalarefresh'] = array(
    'callback' => 'kala_build',
    'description' => dt('Refreses your Pantheon site'),
    'aliases' => array('krefresh', 'kr'),
    'examples' => array(
      'drush kr sitename.dev' => 'Refreshes the code, data and files of your pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
    ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['kaladestroy'] = array(
    'callback' => 'kala_destroy',
    'description' => dt('Removes a pantheon site'),
    'aliases' => array('destroy', 'crush', 'wmb', 'kd'),
    'examples' => array(
      'drush crush sitename.dev' => 'Deletes the Pantheon site. Must use a sitename alias (format "sitename.dev") derived from a valid Pantheon alias as first argument.',
     ),
    'arguments' => array(
      'site' => 'A sitename.dev, derived from a valid Pantheon site alias. Do not use the @pantheon convention for this alias as we are not using it as our site.',
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
function kala_vhost() {

  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);

  $sitename = $site['site'];
  if (!file_exists("/etc/nginx/sites-available/" . $sitename)) {
    if (is_dir("/var/www/" . $sitename)) {
      drush_shell_exec("cp /etc/nginx/sites-available/drupaldefault /tmp/" . $sitename);
      $vhost_default_string = kala_get_file("/tmp/" . $sitename);

      $search = array("drupal.kala", "/var/www/drupal", "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS");
      $replace = array($sitename . ".kala", "/var/www/" . $sitename, "");
      $vhost_default_string = str_replace($search, $replace, $vhost_default_string);


      kala_write_file("/tmp/" . $sitename, $vhost_default_string);
      drush_shell_exec ("cp /tmp/" . $sitename . " /etc/nginx/sites-available/" . $sitename);
      drush_shell_exec ("ln -s /etc/nginx/sites-available/" . $sitename . " /etc/nginx/sites-enabled/" . $sitename);

      drush_shell_exec ("service nginx restart");
      kala_update_etc_hosts($sitename . ".kala");
    }
  }
  else {
    drush_log('Seriously, the vhost file already exists!', 'warning');
  }
}

/**
 *
 */
function kala_code(){

  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);
  $test == $test;

  if ($site['pantheon'] === TRUE) {
    drush_print('Coder, do you already have a local codebase for this site?');
    if (is_dir("/var/www/" . $site['site'])) {
      if (drush_shell_exec("cat /var/www/" . $site['site'] . "/.git/config | grep url")) {
        drush_log('It looks like you might!', 'warning');

        drush_shell_exec("cat /var/www/" . $site['site'] . "/.git/config | grep url > /tmp/gitconfig" . $site['site']);
        $gitconfig_string = trim(file_get_contents("/tmp/gitconfig" . $site['site']));
        drush_shell_exec("rm /tmp/gitconfig" . $site['site']);

        if ($gitconfig_string == "url = ssh://codeserver.dev." . $site['id'] . "@codeserver.dev." . $site['id'] . ".drush.in:2222/~/repository.git") {
          drush_log('Oh you! You have already downloaded this code. I guess we will just refresh it then.', 'warning');
          drush_shell_exec("git --git-dir=/var/www/" . $site['site']. "/.git pull");
          drush_log('And... we refreshed that stale stale code!', 'success');
        }
        else {
          drush_log('Directory /var/www/' . $site['site'] . ' exists... and is not empty... and is a codebase but not the right codebase. Please remove this directory before you attempt to download your codebase. Chump!', 'error');
        }
      }
      else {
        drush_log('Directory /var/www/' . $site['site'] . ' exists... and is not empty... and is not a codebase. Please remove this directory before you attempt to download your codebase. You vicious knave you!', 'error');
      }
    }
    else {
      drush_print('Coder, your code fields are fertile and unblemished. Prepare to receive a potent load of code seed. Also this may take a few minutes so please be patient...');
      // try to connect via ssh
      if (drush_shell_exec("git clone ssh://codeserver.dev." . $site['id'] . "@codeserver.dev." . $site['id'] . ".drush.in:2222/~/repository.git /var/www/" . $site['site'])) {
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

  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);

  if ($site['pantheon'] === TRUE) {
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"create database " . $site['kaladb'] . "\"")) {
      drush_log('Dearest friend, a new database called ' . $site['kaladb'] . ' hath been created', 'success');
    }
    else {
      drush_log('This database already exists! What are you trying to do!!!', 'notice');
    }

    drush_log('Making sure the beast is awake...', 'success');
    if (drush_shell_exec("drush @" . $site['site'] . ".dev status")) {
      drush_log('THE BEAST AWAKENS!', 'success');
    }

    drush_print('Dear sir! We are now attempting a database download, please standby...');
    if (drush_shell_exec("cd /var/www/" . $site['site'] . " && drush pipe @" . $site['site'] . ".dev default -y --disable=pantheon_apachesolr --ssh-options='" . $site['ssh'] . "'")) {
      drush_log('SOMETHING SOMETHING SOMETHING IMPORT COMPLETE', 'success');
    }
    else {
      drush_log('SQL-SYNC seemed to fail... trying to rock it old school instead', 'notice');

      if (drush_shell_exec("mysqldump -u" . $site['db_user'] . " -h" . $site['db_host'] ." -P" . $site['db_port'] ." -p" . $site['db_pass'] . " -CceKqQ --add-drop-table --add-locks --create-options --no-autocommit --single-transaction " . $site['db_db'] ." > /tmp/" . $site['id'] .".sql")) {
        drush_log('data downloaded from pantheon', 'success');
      }
      else {
        drush_log('could not get data from pantheon', 'error');
      }
      if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost " . $site['kaladb'] . " < /tmp/" . $site['id'] .".sql")) {
        drush_log('your pantheon data has been imported to ' . $site['kaladb'], 'success');
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
function kala_files(){

  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);

  if ($site['pantheon'] === TRUE) {
    drush_print('We are now in the process of checking to see whether or not you have tried to sync these here filez before!');
    if (is_dir("/var/www/" . $site['site'] . "/sites/default/files")) {
      drush_log('you have!', 'success');
    }
    else {
      mkdir("/var/www/" . $site['site'] . "/sites/default/files");
      mkdir("/var/www/" . $site['site'] . "/sites/default/private");
      drush_log('Building up some sweet sweet files directories for you', 'success');
      // settings this to 777 for now because its the only way to get file uploads to work properly with nfs sharing
      drush_shell_exec("chmod 777 /var/www/" . $site['site'] . "/sites/default/files");
      drush_shell_exec("chmod 777 /var/www/" . $site['site'] . "/sites/default/files/private");
    }

    drush_log('Doing that funky file sync tango. It feels good. Please wait...', 'success');
    drush_shell_exec("rsync -rlztv --ipv4 -e 'ssh " . $site['ssh'] . "' --exclude 'js' --exclude 'css' --exclude 'ctools' --exclude 'imagecache' --exclude 'xmlsitemap' --exclude 'backup_migrate' --exclude 'styles' --exclude 'less' " . $site['env'] . "." . $site['id'] . "@appserver." . $site['env'] . "." . $site['id'] . ".drush.in:files /var/www/" . $site['site'] . "/sites/default/");
    drush_log('Consider your files N*SYNC', 'success');
  }
  else {
    return;
  }
}

/**
 *
 */
function kala_build() {

  $args = drush_get_arguments();
  $profile = drush_get_option('profile');
  if (!isset($profile)) {
    $profile = 'panopoly';
  }
  $site = _kala_build_site($args[1]);

  drush_print('WE GONE BUILD THIS HERE SITE NOW! STANDBY LADDY/LASS');

  // Get data from panthoen
  if (isset($site['pantheon']) && $site['pantheon'] === TRUE) {
    kala_code($args[1]);
    drush_log('Codebase: Q\'Plah!', 'success');

    _kala_reset_settings($site);
    drush_log('Settings: Rebuilt!, Check git status', 'success');

    kala_data($args[1]);
    drush_log('Database: Q\'Plah!', 'success');

    kala_files($args[1]);
    drush_log('Files: Q\'Plah!', 'success');
  }
  // build a new site
  else {
    // check to see if directory already exists for some weird reason
    if (!is_dir("/var/www/" . $site['site'])) {
      // download distro in webroot
      drush_shell_exec("drush dl " . $profile . " destination=/var/www --drupal-project-rename=" . $site['site'] . " -y");

      // spin up empty DB
      if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"create database " . $site['kaladb'] . "\"")) {
        drush_log('Dearest friend, a new database called ' . $site['kaladb'] . ' hath been created', 'success');
      }

      drush_log('Building a new ' . $profile . 'site.', 'success');
      if (drush_shell_exec("cd /var/www/" . $site['site'] . " && drush site-install " . $profile . " -y --db-url=mysql://root:password@localhost/" . $site['kaladb'] . " --account-pass=admin")) {
        drush_log('Build complete', 'success');
      }
    }
  }

  //
  drush_shell_exec("sudo drush vhost " . $args[1]);
  drush_shell_exec("cd /var/www/" . $site['site']);
  drush_shell_exec("drush cc all -y");
  drush_log('Drush: We clear yo cache', 'success');

  drush_log('Build: Success!', 'success');

  return;
}

/**
 *
 */
function kala_destroy(){

  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);

  if (isset($site['site'])) {
  drush_print('PREPARE TO RIDE ON EL CRUSH BUS');

    if (drush_shell_exec("rm -rf /var/www/" . $site['site'])) {
      drush_log('CODES/FILES = FUCKING CRUSHED', 'success');
    }
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"drop database " . $site['kaladb'] . "\"")) {
      drush_log('DB = FUCKING CRUSHED', 'success');
    }

    if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-available/" . $site['site'])) {
      if (drush_shell_exec("sudo rm -rf /etc/nginx/sites-enabled/" . $site['site'])) {
        drush_log('VHOST = FUCKING CRUSHED', 'success');
      }
    }

    if (drush_shell_exec("sudo service nginx restart")) {
    }

    kala_remove_etc_hosts($site['site'] . ".kala");
    drush_log('SITE = FUCKING CRUSHED', 'success');
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
function _kala_build_site($sitename) {
    // load all available aliases
  drush_sitealias_load_all();
  $aliases = drush_get_context('site-aliases');
  $siteal = explode('.', $sitename);
  $site = array();
  $site['site'] = $siteal[0];
  $site['kaladb'] = str_replace("-", "_", $site['site'] . "_kala");
  $test == $test;

  if (isset($aliases['@' . $sitename])) {
    // honestly don't know what this line is for?
    // $site = explode('.', $aliases['@' . $sitename]['uri']);
    $user = explode('.', $aliases['@' . $sitename]['remote-user']);

    // weak check if alias is valid pantheon alias
    if ($user[0] != 'dev') {
      drush_log('WE ONLY BUILD FROM DEV YO', 'error');
      return FALSE;
    }
    elseif (!isset($aliases['@' . $sitename]['remote-host']) || !isset($aliases['@' . $sitename]['remote-user']) || !isset($aliases['@' . $sitename]['db-url'] )) {
      drush_log('Alias exists but is probably not a validly formatted pantheon alias... doing nothing', 'success');
      return FALSE;
    }
    else {
      // load pantheon environment
      $site['pantheon'] = TRUE;
      $site['env'] = $user[0];
      $site['id'] = $user[1];
      $site['ssh'] = $aliases['@' . $sitename]['ssh-options'] . ' -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no';
      $site['db_url'] = $aliases['@' . $sitename]['db-url'];

      $regex = '/^mysql:\/\/([^:]+):([^@]+)@([^:]+):(\d+)\/(.+)$/';
      $matches = array();
      preg_match($regex, $site['db_url'], $matches);

      $site['db_user'] = $matches[1];
      $site['db_pass'] = $matches[2];
      $site['db_host'] = $matches[3];
      $site['db_port'] = $matches[4];
      $site['db_db'] = $matches[5];

      return $site;
    }
  }
  else {
    $site['env'] = 'kala';
    return $site;
  }
}


/**
 * rebuild settings.php with kala settings
 */
function _kala_reset_settings($site) {
  require_once("/var/www/" . $site['site'] . "/sites/default/settings.php");
  $site['kaladb'] = str_replace("-", "_", $site['site'] . "_kala");

  $output = '';
  if (isset($db_url)) {
    if (strpos($db_url, $site['kaladb']) === FALSE) {
    $settingsfile = "/var/www/" . $site['site'] . "/sites/default/settings.php";
    $fh = fopen($settingsfile, 'a') or die("can't open file");

    $output .= "/** \n";
    $output .= " * Kalabox local settings \n";
    $output .= " */ \n";
    $output .= "// Only use these settings if on Kalabox \n";
    $output .= "if(isset(\$_SERVER['KALABOX']) &&  \$_SERVER['KALABOX'] === 'on') { \n";
    $output .= "  // Presumed kalabox db settings \n";
    $output .= "  \$db_url = 'mysql://root:password@localhost/" . $site["kaladb"] . "';\n";
    $output .= "}\n";

    $settings = $output;

    fwrite($fh, $settings);
    fclose($fh);
    }
  }
  else {
    if ($databases['default']['default']['database'] != $site['kaladb'] ) {

      // haven't decided if we should enforce this or an autocommit or what
      // drush_shell_exec("git --git-dir=/var/www/" . $site['site'] . "/.git update-index --assume-unchanged /var/www/" . $site['site'] . "/sites/default/settings.php");

      $settingsfile = "/var/www/" . $site['site'] . "/sites/default/settings.php";
      $fh = fopen($settingsfile, 'a') or die("can't open file");

      $output .= "/** \n";
      $output .= " * Kalabox local settings \n";
      $output .= " */ \n";
      $output .= "// Only use these settings if on Kalabox \n";
      $output .= "if(isset(\$_SERVER['KALABOX']) && \$_SERVER['KALABOX'] === 'on') { \n";
      $output .= "  // Presumed kalabox db settings \n";
      $output .= "  \$databases['default']['default'] = array( \n";
      $output .= "    'driver' => 'mysql',\n";
      $output .= "    'database' => '" . $site['kaladb'] . "', \n";
      $output .= "    'username' => 'root',\n";
      $output .= "    'password' => 'password',\n";
      $output .= "    'host' => 'localhost',\n";
      $output .= "    'prefix' => '',\n";
      $output .= "  );\n";
      $output .= "\n";
      $output .= "  // Set some common desirable local vars  \n";
      $output .= "  \$conf['file_temporary_path'] = '/tmp';\n";
      $output .= "  \$conf['file_public_path'] = 'sites/default/files';  \n";
      $output .= "  \$conf['file_private_path'] = 'sites/default/files/private';  \n";
      $output .= "  \$conf['reroute_email_enable'] = 1;  \n";
      $output .= "  \$conf['cache'] = 0;  \n";
      $output .= "  \$conf['css_gzip_compression'] = FALSE;  \n";
      $output .= "  \$conf['js_gzip_compression'] = FALSE;  \n";
      $output .= "}\n";
      $output .= "\n";

      $settings = $output;
      fwrite($fh, $settings);
      fclose($fh);
    }
  }
}

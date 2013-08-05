<?php

/**
 * @file
 *   kala.drush.inc
 *
 */

// Set our own log printing function:
drush_set_context('DRUSH_LOG_CALLBACK', '_kala_print_log');

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
      'site-name' => array(
        'description' => 'Human readable meta data',
        'example-value' => '"My Awesome Site",BeastMode',
      ),
      'files' => array(
        'description' => 'Use this flag to also download your files',
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
 * Creates a vhost for a newly built or created site
 */
function kala_vhost() {
  // Get the site machine name and parse it correctly
  $args = drush_get_arguments();
  $siteal = explode('.', $args[1]);
  $sitename = $siteal[0];

  // Create a vhost if it doesnt already exit
  if (!file_exists("/etc/kalastack/vhosts/sites-available/" . $sitename)) {
    // Make sure a site is actually where it is supposed to be
    if (is_dir("/var/www/" . $sitename)) {
      drush_shell_exec("cp /etc/nginx/sites-available/drupaldefault /tmp/" . $sitename);
      $vhost_default_string = kala_get_file("/tmp/" . $sitename);

      //  Load up default drupal vhost and update with new site info
      $search = array("drupal.kala", "/var/www/drupal", "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS");
      $replace = array($sitename . ".kala", "/var/www/" . $sitename, "");
      $vhost_default_string = str_replace($search, $replace, $vhost_default_string);

      // Write the file and symlink it to sites-enabled
      kala_write_file("/tmp/" . $sitename, $vhost_default_string);
      drush_shell_exec ("cp /tmp/" . $sitename . " /etc/kalastack/vhosts/sites-available/" . $sitename);
      drush_shell_exec ("ln -s /etc/kalastack/vhosts/sites-available/" . $sitename . " /etc/kalastack/vhosts/sites-enabled/" . $sitename);

      // Restart nginx so the site actually is active
      drush_shell_exec ("service nginx restart");
      kala_update_etc_hosts($sitename . ".kala");
      drush_log('New vhost created!', 'success');
    }
  }
  else {
    // File already exists!
    drush_log('Seriously, the vhost file already exists!', 'warning');
  }
}

/**
 * [kala_code description]
 * @param  array or string $site an array of the sites info or the uparsed machine argument
 * @return only on error
 */
function kala_code($site = NULL){
  // Load up site only if it hasnt been passed in
  $args = drush_get_arguments();
  if (!is_array($site)) {
    $site = _kala_build_site($args[1]);
  }

  // Only attempt if this is a pantheon site
  if ($site['pantheon'] === TRUE) {
    drush_print('Coder, do you already have a local codebase for this site?');
    // The codebase might already exist
    if (is_dir("/var/www/" . $site['site'])) {
      if (drush_shell_exec("cat /var/www/" . $site['site'] . "/.git/config | grep url")) {
        drush_log('It looks like you might!', 'warning');
        drush_shell_exec("cat /var/www/" . $site['site'] . "/.git/config | grep url > /tmp/gitconfig" . $site['site']);
        $gitconfig_string = trim(file_get_contents("/tmp/gitconfig" . $site['site']));
        drush_shell_exec("rm /tmp/gitconfig" . $site['site']);
        // Codebase does exist
        if ($gitconfig_string == "url = ssh://codeserver.dev." . $site['id'] . "@codeserver.dev." . $site['id'] . ".drush.in:2222/~/repository.git") {
          drush_log('Oh you! You have already downloaded this code. I guess we will just refresh it then.', 'warning');
          drush_shell_exec("git --git-dir=/var/www/" . $site['site']. "/.git pull");
          drush_log('And... we refreshed that stale stale code!', 'success');
        }
        // A codebase exists but it is the wrong one
        else {
          drush_log('Directory /var/www/' . $site['site'] . ' exists... and is not empty... and is a codebase but not the right codebase. Please remove this directory before you attempt to download your codebase. Chump!', 'error');
        }
      }
      // Files alraedy in the folder that arent a git repo
      else {
        drush_log('Directory /var/www/' . $site['site'] . ' exists... and is not empty... and is not a codebase. Please remove this directory before you attempt to download your codebase. You vicious knave you!', 'error');
      }
    }
    // Git clone for the first time
    else {
      drush_print('Coder, your code fields are fertile and unblemished. Prepare to receive a potent load of code seed. Also this may take a few minutes so please be patient...');
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
 * This creates a new DB and fills it with data from pantheon, or refreshs that data if it already exists
 * @param  array or string $site an array of the sites info or the uparsed machine argument
 * @return only on failure
 */
function kala_data($site = NULL){
  // Load uo site only if it hasnt been passed in
  $args = drush_get_arguments();
  if (!is_array($site)) {
    $site = _kala_build_site($args[1]);
  }

  // Only try this if its a pantheon site
  if ($site['pantheon'] === TRUE) {
    // Create a new database if it doesnt already exist
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"create database " . $site['kaladb'] . "\"")) {
      drush_log('Dearest friend, a new database called ' . $site['kaladb'] . ' hath been created', 'success');
    }
    else {
      drush_log('This database already exists! What are you trying to do!!!', 'notice');
    }

    // Making sure the pantheon DB server is awake
    drush_log('Making sure the beast is awake...', 'success');
    if (drush_shell_exec("drush @" . $site['site'] . ".dev status")) {
      drush_log('THE BEAST AWAKENS!', 'success');
    }

    // Downloading and importing the data
    drush_print('Dear sir! We are now attempting a database download, please standby...');
    // Trying SQL-SYNC-PIPE first
    if (drush_shell_exec("cd /var/www/" . $site['site'] . " && drush pipe @" . $site['site'] . ".dev default -y --disable=pantheon_apachesolr --ssh-options='" . $site['ssh'] . "'")) {
      drush_log('SOMETHING SOMETHING SOMETHING IMPORT COMPLETE', 'success');
    }
    // Using ghetto method if SSP fails
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
 * Downloads or refreshs pantheon files
 * @param  array or string $site an array of the sites info or the uparsed machine argument
 * @return if fails
 */
function kala_files($site){
  // Load up site byt only if not passed in
  $args = drush_get_arguments();
  if (!is_array($site)) {
    $site = _kala_build_site($args[1]);
  }

  // Only run if its a panthoen site
  if ($site['pantheon'] === TRUE) {
    // Checking ot see ig the files firectory exists already
    drush_print('We are now in the process of checking to see whether or not you have tried to sync these here filez before!');
    if (is_dir("/var/www/" . $site['site'] . "/sites/default/files")) {
      drush_log('you have!', 'success');
    }
    // Build the files directory and set its permissions if it doesnt exist yet
    else {
      mkdir("/var/www/" . $site['site'] . "/sites/default/files");
      mkdir("/var/www/" . $site['site'] . "/sites/default/private");
      drush_log('Building up some sweet sweet files directories for you', 'success');
      // Settings this to 777 for now because its the only way to get file uploads to work properly with nfs sharing
      drush_shell_exec("chmod 777 /var/www/" . $site['site'] . "/sites/default/files");
      drush_shell_exec("chmod 777 /var/www/" . $site['site'] . "/sites/default/files/private");
    }

    // RSYNCing files from pantheon
    drush_log('Doing that funky file sync tango. It feels good. Please wait...', 'success');
    drush_shell_exec("rsync -rlztv --ipv4 -e 'ssh " . $site['ssh'] . "' --exclude 'js' --exclude 'css' --exclude 'ctools' --exclude 'imagecache' --exclude 'xmlsitemap' --exclude 'backup_migrate' --exclude 'styles' --exclude 'less' " . $site['env'] . "." . $site['id'] . "@appserver." . $site['env'] . "." . $site['id'] . ".drush.in:files /var/www/" . $site['site'] . "/sites/default/");
    drush_log('Consider your files N*SYNC', 'success');
  }
  else {
    return;
  }
}



/**
 * Create a new and fully instantiated site or build one that already exist on pantheon
 * @return when complete
 */
function kala_build() {

  // Grab arguments and options
  $args = drush_get_arguments();
  $profile = drush_get_option('profile');
  $files = drush_get_option('files');
  $site_name = drush_get_option('site-name');

  // Set a default profile if not set
  if (!isset($profile)) {
    $profile = 'panopoly';
  }

  // Build an array of info for the site
  $site = _kala_build_site($args[1]);

  // START IT UP!
  drush_print('WE GONE BUILD THIS HERE SITE NOW! STANDBY LADDY/LASS');

  // Build a pantheon site
  if (isset($site['pantheon']) && $site['pantheon'] === TRUE) {
    // Get the code
    kala_code($site);
    drush_log('Codebase: Q\'Plah!', 'success');

    // Add some settings for kalabox
    _kala_reset_settings($site);
    drush_log('Settings: Rebuilt!, Check git status', 'success');

    // Get the data
    kala_data($site);
    drush_log('Database: Q\'Plah!', 'success');

    // Get the files but only run if option is set to do so
    if ($files) {
      kala_files($site);
      drush_log('Files: Q\'Plah!', 'success');
    }
  }
  // Spin up a new site
  else {
    // Check to see if directory already exists for some weird reason
    if (!is_dir("/var/www/" . $site['site'])) {
      // Set sitename
      $site['site-name'] = $site_name ? $site_name : $site['site'];

      // Download distro in webroot
      drush_log('We are now downloading the ' . $profile . ' distribution', 'success');
      drush_shell_exec("cd /var/www && drush dl " . $profile . " --drupal-project-rename=" . $site['site'] . " -y");

      // Spin up empty DB
      if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"create database " . $site['kaladb'] . "\"")) {
        drush_log('Dearest friend, a new database called ' . $site['kaladb'] . ' hath been created', 'success');
      }

      // Run the site install
      drush_log('Building a new ' . $profile . 'site.', 'success');
      if (drush_shell_exec("cd /var/www/" . $site['site'] . " && drush site-install " . $profile . " -y --db-url=mysql://root:password@localhost/" . $site['kaladb'] . " --account-pass=admin")) {
        drush_log('Build complete', 'success');
      }
    }
  }

  // Vhost and cleanupz
  drush_shell_exec("sudo drush vhost " . $args[1]);
  drush_shell_exec("cd /var/www/" . $site['site'] . " && drush cc all -y");
  drush_log('Drush: We clear yo cache', 'success');
  _kala_add_alias($site);
  drush_log('Success: ' . $site['site-name'] .   ' has been built!', 'success');

  return;
}

/**
 * Oblierate a local site
 */
function kala_destroy(){

  // Get and parse sitename
  $args = drush_get_arguments();
  $site = _kala_build_site($args[1]);

  // If that site actually exists...
  if (isset($site['site'])) {
  drush_print('PREPARE TO RIDE ON EL CRUSH BUS');

    // Remove Code and Files
    if (drush_shell_exec("rm -rf /var/www/" . $site['site'])) {
      drush_log('CODES/FILES = FUCKING CRUSHED', 'success');
    }

    // Remove Data
    if (drush_shell_exec("mysql -uroot -ppassword -hlocalhost -e \"drop database " . $site['kaladb'] . "\"")) {
      drush_log('DB = FUCKING CRUSHED', 'success');
    }

    // Remove VHOST
    if (drush_shell_exec("sudo rm -rf /etc/kalastack/vhosts/sites-available/" . $site['site'])) {
      if (drush_shell_exec("sudo rm -rf /etc/kalastack/vhosts/sites-enabled/" . $site['site'])) {
        drush_log('VHOST = FUCKING CRUSHED', 'success');
      }
    }

    // Restart nginx
    drush_shell_exec("sudo service nginx restart");

    // Remove hosts entry
    kala_remove_etc_hosts($site['site'] . ".kala");
    _kala_remove_alias($site);
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

/**
 * Update the hosts file
 * @param  [string] $hostname [the hostname to be added]
 */
function kala_update_etc_hosts($hostname) {
    // Create new hosts file
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

/**
 * Remove hostname from hosts file
 * @param  [string] $hostname [the hostname to be added]
 */
function kala_remove_etc_hosts($hostname) {
  // Remove hosts
  drush_shell_exec("sed /" . $hostname . "/d /etc/hosts > /tmp/hosts");
  drush_shell_exec("sudo cp -f /tmp/hosts /etc/hosts");
  drush_shell_exec("rm /tmp/hosts");
}


/**
 * Put together meaningful information about the site about to be created/built
 * @param  [string] $sitename [machine name of the host]
 * @return if fails
 */
function _kala_build_site($sitename) {
    // Load all available aliases and remove suffix
  drush_sitealias_load_all();
  $aliases = drush_get_context('site-aliases');
  $siteal = explode('.', $sitename);
  $site = array();

  // Set site machinename and locald b name
  $site['site'] = $siteal[0];
  $site['kaladb'] = str_replace("-", "_", $site['site'] . "_kala");

  // Build some common elements
  if (isset($aliases['@' . $sitename])) {
    // Honestly don't know what this line is for?
    // $site = explode('.', $aliases['@' . $sitename]['uri']);
    $user = explode('.', $aliases['@' . $sitename]['remote-user']);

    // Weak check if alias is valid pantheon alias
    if ($user[0] != 'dev') {
      drush_log('WE ONLY BUILD FROM DEV YO', 'error');
      return FALSE;
    }
    elseif (!isset($aliases['@' . $sitename]['remote-host']) || !isset($aliases['@' . $sitename]['remote-user']) || !isset($aliases['@' . $sitename]['db-url'] )) {
      drush_log('Alias exists but is probably not a validly formatted pantheon alias... doing nothing', 'success');
      return FALSE;
    }
    else {
      // Load pantheon environmental vars
      $site['pantheon'] = TRUE;
      $site['env'] = $user[0];
      $site['id'] = $user[1];
      $site['ssh'] = $aliases['@' . $sitename]['ssh-options'] . ' -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no';
      $site['db_url'] = $aliases['@' . $sitename]['db-url'];
      $site['built-from'] = $sitename;

      // Get Human Readable Sitename
      drush_shell_exec("drush @" . $sitename . " vget site_name");
      $drush_site_name = drush_shell_exec_output();
      preg_match('/\"([^\"]+)\"/', $drush_site_name[0], $matches);
      $site['site-name'] = $matches[1];

      // Split out database
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
 * Adds in local kalabox settings to settings.php
 * @param  [array] $site [useful site info]
 */
function _kala_reset_settings($site) {
  // Get the sites settings.php file
  require_once("/var/www/" . $site['site'] . "/sites/default/settings.php");
  // Replace naughty mysql chars
  $site['kaladb'] = str_replace("-", "_", $site['site'] . "_kala");

  $output = '';
  // Build Drupal 6 DB string
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
  // Build Drupal 7 DB array
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

/**
 * Build a local alias
 * @param  array or string $site an array of the sites info or the uparsed machine argument
 */
function _kala_add_alias($site) {
  // Load up site but only if not passed in
  $args = drush_get_arguments();
  if (!is_array($site)) {
    $site = _kala_build_site($args[1]);
  }

  // Create an aliases file if there are no local sites
  if (!file_exists("/etc/kalastack/aliases/aliases.drushrc.php")) {
    file_put_contents("/etc/kalastack/aliases/aliases.drushrc.php", "");
  }

  // Load the kala aliases file
  require '/etc/kalastack/aliases/aliases.drushrc.php';
  if (!isset($aliases[$site['site'] . '.kala'])) {
    // Build the local alias
    $aliases[$site['site'] . '.kala'] = array(
      'root' => '/var/www/' . $site['site'],
      'uri' => $site['site'] . '.kala',
      'read-name' => $site['site-name'],
    );
    // If built from somewhere, indicate that here
    if ($site['built-from']) {
      $aliases[$site['site'] . '.kala']['built-from'] = $site['built-from'];
    }
  }

  // Build output
  $output = "<?php \n\n";
  foreach ($aliases as $key => $value) {
    $output .= "\$aliases['" . $key . "'] = array(\n";
    $output .= "  'root' => '" . $value['root'] . "',\n";
    $output .= "  'uri' => '" . $value['uri'] . "',\n";
    $output .= "  'read-name' => '" . $value['read-name'] .  "',\n";
    // Only include built froms if they exist
    if ($value['built-from']) {
      $output .= "  'built-from' => '" . $value['built-from'] .  "',\n";
    }
    $output .= ");\n";
  }

  // Write file
  file_put_contents("/etc/kalastack/aliases/aliases.drushrc.php", $output);
}

/**
 * Remove a local alias
 * @param  array or string $site an array of the sites info or the uparsed machine argument
 */
function _kala_remove_alias($site) {
  // Load up site but only if not passed in
  $args = drush_get_arguments();
  if (!is_array($site)) {
    $site = _kala_build_site($args[1]);
  }

  // Load alias file if it exists
  if (file_exists("/etc/kalastack/aliases/aliases.drushrc.php")) {
    require '/etc/kalastack/aliases/aliases.drushrc.php';
  }
  else {
    return;
  }

  // Load the kala aliases file
  if (isset($aliases[$site['site'] . '.kala'])) {
    unset($aliases[$site['site'] . '.kala']);
  }

  // Build output
  $output = "<?php \n\n";
  foreach ($aliases as $key => $value) {
    $output .= "\$aliases['" . $key . "'] = array(\n";
    $output .= "  'root' => '" . $value['root'] . "',\n";
    $output .= "  'uri' => '" . $value['uri'] . "',\n";
    $output .= "  'read-name' => '" . $value['read-name'] .  "',\n";
    $output .= "  'built-from' => '" . $value['built-from'] .  "',\n";
    $output .= ");\n";
  }

  // Write file
  file_put_contents("/etc/kalastack/aliases/aliases.drushrc.php", $output);
}

/**
 * Override of _drush_print_log().
 * It's mostly the same except for having non-error mesages print to standard
 * out instead of standard error.
 */
function _kala_print_log($entry) {
  if (drush_get_context('DRUSH_NOCOLOR')) {
    $red = "[%s]";
    $yellow = "[%s]";
    $green = "[%s]";
  }
  else {
    $red = "\033[31;40m\033[1m[%s]\033[0m";
    $yellow = "\033[1;33;40m\033[1m[%s]\033[0m";
    $green = "\033[1;32;40m\033[1m[%s]\033[0m";
  }

  $verbose = drush_get_context('DRUSH_VERBOSE');
  $debug = drush_get_context('DRUSH_DEBUG');

  $return = TRUE;
  $output_type = NULL; // Will default to standard out.
  switch ($entry['type']) {
    case 'warning':
    case 'cancel':
      $type_msg = sprintf($yellow, $entry['type']);
      break;
    case 'failed':
    case 'error':
      $type_msg = sprintf($red, $entry['type']);
      $return = FALSE;
      $output_type = STDERR;
      break;
    case 'ok':
    case 'completed':
    case 'success':
    case 'status':
      // In quiet mode, suppress progress messages
      if (drush_get_context('DRUSH_QUIET')) {
        return TRUE;
      }
      $type_msg = sprintf($green, $entry['type']);
      break;
    case 'notice':
    case 'message':
    case 'info':
      if (!$verbose) {
        // print nothing. exit cleanly.
        return TRUE;
      }
      $type_msg = sprintf("[%s]", $entry['type']);
      break;
    default :
      if (!$debug) {
        // print nothing. exit cleanly.
        return TRUE;
      }
      $type_msg = sprintf("[%s]", $entry['type']);
      break;
  }

  // When running in backend mode, log messages are not displayed, as they will
  // be returned in the JSON encoded associative array.
  if (drush_get_context('DRUSH_BACKEND')) {
    return $return;
  }

  $columns = drush_get_context('DRUSH_COLUMNS', 80);

  $width[1] = 11;
  // Append timer and memory values.
  if ($debug) {
    $timer = sprintf('[%s sec, %s]', round($entry['timestamp'] -DRUSH_REQUEST_TIME, 2), drush_format_size($entry['memory']));
    $entry['message'] = $entry['message'] . ' ' . $timer;
  }

  $width[0] = ($columns - 11);

  $format = sprintf("%%-%ds%%%ds", $width[0], $width[1]);

  // Place the status message right aligned with the top line of the error message.
  $message = wordwrap($entry['message'], $width[0]);
  $lines = explode("\n", $message);
  $lines[0] = sprintf($format, $lines[0], $type_msg);
  $message = implode("\n", $lines);
  drush_print($message, 0, $output_type);
  return $return;
}

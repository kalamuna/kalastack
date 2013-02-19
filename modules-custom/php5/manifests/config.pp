/**
 * 
 * Builds a basic php.ini file for CLI
 * 
 */
class php5::config {
	
	php5::ini { "cli": 
	  path => "/etc/php5/cli/php.ini",
	  disable_functions => "",
	  max_execution_time => 0,
	  max_input_time => -1,
	  memory_limit => -1,
	  error_reporting => "E_ALL & ~E_DEPRECATED",
	  display_errors => "Off",
	  track_errors => "Off",
	  html_errors => "Off",
	  error_log => "/var/log/php_cli_errors.log",
	  post_max_size => "200M",
	  upload_max_filesize => "200M",
	  require => Class["php5::install"],
	}

}
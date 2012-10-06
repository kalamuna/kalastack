
class phpfpm::extensions::xdebug (
	$remote_enable = "On",
	$remote_host = "kala",
	$remote_port  = 9000,
	$remote_handler = "dbgp",
	$profiler_enable = 1,
	$profile_output_dir = "/tmp/xprofile",
	$collect_params = "On",
	$show_local_vars = "On",
	
){

  phpfpm::extension { "php5-xdebug": }
  
  file {
    "xdebug.ini":
      ensure => file,
      path      => "/etc/php5/conf.d/xdebug.ini",
      require => Class["phpfpm::install"],
      notify => [Class["phpfpm::service"], Class["nginx::service"]],
      content   => template("phpfpm/extensions/xdebug.ini.erb")
  } 
  
}

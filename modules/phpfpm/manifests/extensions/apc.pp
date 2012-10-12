
class phpfpm::extensions::apc (
	$enabled  = 1,
	$shm_size = "128M",
	$rfc1867  = 1
){

  phpfpm::extension { "php-apc": }
  
  file {
    "apc.ini":
      ensure => file,
      path      => "/etc/php5/conf.d/apc.ini",
      require => Class["phpfpm::install"],
      notify => [Class["phpfpm::service"], Class["nginx::service"]],
      content   => template("phpfpm/extensions/apc.ini.erb")
  } 
}
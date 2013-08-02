/**
 *
 * Installs and configures the APC extension for PHP5
 *
 */
class phpfpm::extensions::apc (

	$enabled  = 1,
	$rfc1867  = 1,

){

  # Dynamically set shmsize, but don't exceed 1G
  # Trick puppe tinto thinking this is a number

  $apc_total_mem = 0 + $::kalamem
  $apc_shm_size = $apc_total_mem / 10
  if ($apc_shm_size > 256) {
    $shm_size = "256M"
  }
  else {
    $shm_size = $apc_shm_size
    $shm_size = "${shm_size}M"
  }

  phpfpm::extension { "php-apc": version => present, }

  file {
    "apc.ini":
      ensure => file,
      path      => "/etc/php5/conf.d/apc.ini",
      require => Class["phpfpm::install"],
      notify => [Class["phpfpm::service"], Class["nginx::service"]],
      content   => template("phpfpm/extensions/apc.ini.erb")
  }

}

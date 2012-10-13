/**
 * 
 * Definition for a PHP5 extension
 * 
 */
define phpfpm::extension (
    
  $version,
  
){
  
  package { "${name}":
    ensure => "${version}",
    require => Class["phpfpm::install"],
    notify => [Class["phpfpm::service"], Class["nginx::service"]],
  }
  
}

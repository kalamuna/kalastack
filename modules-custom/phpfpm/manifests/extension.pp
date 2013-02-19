/**
 * 
 * Definition for a PHP5 extension
 * 
 */
define phpfpm::extension (
    
  $version,
  
){
  
  package { "${name}":
    ensure => "present",
    require => Class["phpfpm::install"],
    notify => [Class["phpfpm::service"], Class["nginx::service"]],
  }
  
}

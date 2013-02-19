/**
 * 
 * add kala_user to www-data
 * 
 */
class nginx::config {
        
    # add kalauser to www-data group
    exec { "www-data":
      path => "/bin:/usr/bin",
      unless => "id ${::kala_user} | grep www-data",
      command => "sudo usermod -g www-data ${::kala_user}",
      require => Class["nginx::install"],
      notify => Class["nginx::service"],
    }
    
}
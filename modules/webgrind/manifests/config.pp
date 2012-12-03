/**
 * 
 * Set up xdebug cong for webgrind
 * 
 */
class webgrind::config {
  
  file { "webgrind.ini":
    ensure => file,
    path      => "/etc/php5/conf.d/webgrind.ini",
    require => Class["phpfpm::extensions::xdebug"],
    notify => [Class["phpfpm::service"], Class["nginx::service"]],
    content   => template("webgrind/webgrind.ini.erb")
  } 
  
  phpfpm::nginx::vhost { "webgrind":
    server_name => "grind.kala",
    root        => "/var/www/webgrind",
  }
  
}

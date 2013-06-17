/**
 *
 * Configure nginx
 * 
 */
class nginx::config {
  nginx::conf { "nginx.conf":
    path    => "/etc/nginx/nginx.conf",
    require => Class["nginx::install"],
    notify  => Class["nginx::service"],
  }
  
  file { "/etc/nginx/fastcgi_params":
    ensure => file,
    source => "puppet:///modules/nginx/fastcgi_params",
  }
}
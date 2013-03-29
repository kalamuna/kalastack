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
}
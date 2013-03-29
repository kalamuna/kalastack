/**
 *
 * Defines and sets default values for a nginx.conf file
 */
define nginx::conf (
  # basic settings
  $path = "/etc/nginx/nginx.conf",
  $user = $::kalauser,) {
  file { "${path}":
    path    => "${path}",
    content => template("nginx/nginx.conf.erb"),
  }
}
/**
 *
 * Makes sure the apparmor service is running
 *
 */
class apparmor::service {

  service { "apparmor":
    ensure      => running,
    name        => "apparmor",
    hasstatus   => true,
    hasrestart  => true,
    enable      => true,
  }

}

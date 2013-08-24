/**
 *
 * Upgrade to drush 5
 */
class drush::upgrade {
  # upgrade to drush 5
  exec { "drushupgrade":
    path    => "/bin:/usr/bin",
    unless  => "drush --version | grep 5.",
    command => "sudo drush dl drush-7.x-5.9 --destination='/usr/share' -y",
    require => Class["drush::install"],
  }
}

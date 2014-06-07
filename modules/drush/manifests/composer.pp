/**
 *
 * Installs Terminus
 *
 */
class drush::composer {

  exec { "installcomposer":
    path    => "/bin:/usr/bin:/usr/local/bin",
    unless  => "ls /usr/local/bin | grep composer",
    command => "curl -sS https://getcomposer.org/installer | php && mv composer.phar /usr/local/bin/composer",
    require => [Class["phpfpm::extensions::curl"], Class["phpfpm::extensions::apc"], Class["php5::install"]],
  }

  exec { "set composer global bin path":
    path    => "/bin:/usr/bin:/usr/local/bin",
    unless  => "cat .bashrc | grep 'export PATH=\"$HOME/.composer/vendor/bin:$PATH\"'",
    command => "sed -i '1i export PATH=\"$HOME/.composer/vendor/bin:$PATH\"' $HOME/.bashrc && source $HOME/.bashrc",
    require => Exec["installcomposer"],
  }

}

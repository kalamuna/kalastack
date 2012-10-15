/**
 * 
 * Configures PHPMYADMIN
 * 
 */
class phpmyadmin::config {

    # Makes a nginx vhost for phpmyadmin
	phpfpm::nginx::vhost { "phpmyadmin":
		vhost => "phpmyadmin",
		root => "/usr/share/phpmyadmin",
		server_name => "php.kala",
		index => "index.php",
		upstream => "unix:/tmp/php-fpm.sock",
		custom => "",
		options => {},
	} 
	
	# Sets some basic vars for phpmyadmin
	$php_pass = $mysql::server::install::password
	$pma_db = "phpmyadmin"
	$pma_user = "root"
	$pma_pass = "password"
	$pma_server = "kala"
	
	# Builds the phpmyadmin config DB
    exec { "phpmyadmindbconfig":
	  path => "/bin:/usr/bin",
	  unless => "mysql -uroot -p${php_pass} ${pma_db}",
	  command => "gunzip < /usr/share/doc/phpmyadmin/examples/create_tables.sql.gz | mysql -u${pma_user} -p${pma_pass} -h${pma_server}",
	  require => [
	  	Class[phpmyadmin::install],
	  	Class[network::config]
	  ],
	}
	
	# Adds the pma user
	exec { "phpmyadmincontrolconfig":
	  path => "/bin:/usr/bin",
	  unless => "mysqladmin -u${pma_user} -p${pma_pass} status",
	  command => "mysql -u${pma_user} -p${pma_pass} -h${pma_server} -e \"GRANT ALL PRIVILEGES ON ${pma_db}.* TO ${pma_user}@${pma_server} IDENTIFIED BY '${pma_pass}';\"",
	  require => Exec["phpmyadmindbconfig"],
	}
	
	# Provides a custom config file
	file{ "/etc/phpmyadmin/config.inc.php":
        path => "/etc/phpmyadmin/config.inc.php",
        ensure => present,
        content => template("phpmyadmin/config.inc.php.erb"),
		owner => "root",
		group => "root",
        mode => 0444,
        require => Class[phpmyadmin::install],
    }
    
    # Sets the above creds for the DB
    file{ "/etc/phpmyadmin/config-db.php":
        path => "/etc/phpmyadmin/config-db.php",
        ensure => present,
        content => template("phpmyadmin/config-db.php.erb"),
		owner => "root",
		group => "root",
        mode => 0444,
        require => Class[phpmyadmin::install],
    }
    
}
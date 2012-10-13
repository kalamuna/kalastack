/**
 * 
 * Installs and configures the puppet agent
 * 
 */
class puppet {
	include puppet::install, puppet::config, puppet::service
}
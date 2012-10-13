/**
 * 
 * Installs and configurs SOLR to run inside of TOMCAT6
 * 
 */
class solr {
  include solr::params, solr::install, solr::service
}
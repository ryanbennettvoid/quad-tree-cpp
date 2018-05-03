
const Promise = require( 'bluebird' );
const fs = Promise.promisifyAll( require( 'fs' ) );

const filepath = './data/USA-McDonalds.csv';

const importer = {};

importer.getItems = () => {

  return fs.readFileAsync( filepath, 'utf8' )
  .then( ( items ) => {

    return items.split( /\r\n|\n/ )
    .filter( ( o ) => !!o )
    .map( ( line ) => {
      const [ lat, lng ] = ( line||'' ).split( ',' );
      return { lat: parseFloat( lat ), lng: parseFloat( lng ) };
    } )
    .filter( ( item ) => {
      return typeof item.lat === 'number' && typeof item.lng === 'number';
    } )
    ;

  } )
  ;

};

module.exports = importer;
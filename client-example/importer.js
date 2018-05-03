
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
      const [ lng, lat, name, country, address, phone_number ] = ( line||'' ).split( ',' );
      return {
        lat: parseFloat( lat ),
        lng: parseFloat( lng ),
        data: {
          name,
          country,
          address,
          phone_number
        }
      };
    } )
    .filter( ( item ) => {
      return typeof item.lat === 'number' && typeof item.lng === 'number';
    } )
    ;

  } )
  ;

};

module.exports = importer;
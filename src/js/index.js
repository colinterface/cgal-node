const CGAL = require('bindings')('addon');

const pointA = [1, 1];
console.log('pointA: ', pointA);

const pointB = [2, 2];
console.log('pointB: ', pointB);

const pointC = [3, 3];
console.log('pointC: ', pointC);

const args = [
  ...pointA,
  ...pointB,
  ...pointC,
];

const orientation = CGAL.orientation(...args);
console.log('orientation: ', orientation);

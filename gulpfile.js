var gulp = require('gulp');
var mkdirp = require('mkdirp');

var exec = require('child_process').exec;
var cwd = process.cwd();
var buildDir = cwd + '-build';

var cmakeCmd = "cmake " + cwd;

var env = process.env;
var envCopy = {};

// Copy process.env into envCopy
for (varName in env) {
  envCopy[varName] = env[varName];
}
// Forcibly use clang / clang++
envCopy['CC'] = '/usr/bin/clang';
envCopy['CXX'] = '/usr/bin/clang++';

gulp.task('cmake', function(cb) {
  console.log('Building in ' + buildDir);
  mkdirp(buildDir);
  process.chdir(buildDir);
  exec(cmakeCmd, { env: envCopy }, function (error, stdout, stderr) {
    console.log(stdout);
    console.log(stderr);
    cb(error);
  });
});

gulp.task('build', ['cmake'], function(cb) {
  exec("make all", function (error, stdout, stderr) {
    console.log(stdout);
    console.log(stderr);
    cb(error);
  });
});

gulp.task('watch', ['build'], function() {
  process.chdir(cwd);
  gulp.watch('./CMakeLists.txt', ['build']);
  gulp.watch('./**/CMakeLists.txt', ['build']);
  gulp.watch('lib/**/*.cpp', ['build']);
  gulp.watch('include/**/*.hpp', ['build']);
});

gulp.task('default', ['watch'], function() {});

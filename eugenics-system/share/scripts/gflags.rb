require 'formula'

class Gflags < Formula
  homepage 'http://code.google.com/p/google-gflags/'
  #url 'https://gflags.googlecode.com/files/gflags-2.0.tar.gz'
  #sha1 'dfb0add1b59433308749875ac42796c41e824908'
  url 'https://github.com/schuhschuh/gflags/archive/v2.1.1.tar.gz'
  sha1 '59b37548b10daeaa87a3093a11d13c2442ac6849'
  head "https://github.com/schuhschuh/gflags.git"

  depends_on "cmake" => :build

  def install
    mkdir "build" do
      system "cmake", "..", "-DCMAKE_INSTALL_PREFIX='#{prefix}' -DCMAKE_BUILD_TYPE=None -Wno-dev -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON "
      system "make", "install"
    end
  end
end

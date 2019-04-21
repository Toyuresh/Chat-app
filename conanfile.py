from conans import ConanFile, CMake


class ChatserverConan(ConanFile):
    name = "ChatServer"
    version = "0.1"
    license = "Boost Software License"
    author = "Toyuresh"
    url = "https://github.com/Toyuresh/Chat-app"
    description = "Simple chat-app"
    topics = ("Chat-app", "chat-server", "Website")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"
    requires = "boost/1.70.0@conan/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.hpp", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.exe",dst="bin",keep_path=False)
        self.copy("*.obj", dst="lib",keep_path=False)
        self.copy("*.html", dst="bin", src="src")

    def package_info(self):
        self.cpp_info.libs = ["server"]
        self.cpp_info.obj = ["websocket_session"]
        self.cpp_info.obj = ["http_session"]

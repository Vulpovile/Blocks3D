pipeline {
    agent {label 'windows'}
    environment { 
		CL='/I"C:\\libraries\\g3d-6_10\\include" /I"C:\\libraries\\SDL-1.2.15\\include" /I"C:\\libraries\\ode\\include"'
		LINK='/LIBPATH:C:\\libraries\\g3d-6_10\\win32-7-lib /LIBPATH:C:\\libraries\\SDL-1.2.15\\lib\\x86 /LIBPATH:"C:\\libraries\\ode\\lib7"'
    }
    stages {
        stage('Build') {
            steps {
                bat """
					call "c:\\Program Files (x86)\\Microsoft Visual Studio .NET 2003\\Common7\\Tools\\vsvars32.bat"
					devenv "Blocks3D VS2003.sln" /build release
                """
            }
        }
    }
}
 

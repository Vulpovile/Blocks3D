pipeline {
	agent {label 'windows'}
	stages {
		stage('Build') {
			steps {
				bat """
					call "c:\\Program Files (x86)\\Microsoft Visual Studio .NET 2003\\Common7\\Tools\\vsvars32.bat"
					devenv "Blocks3D VS2003.sln" /build release
				"""
			}
		}
		stage('Package') {
			steps {
				bat """
					"C:\\Program Files (x86)\\Inno Setup 5\\ISCC" Installer\\install_script_vs2003.iss
					"C:\\Program Files (x86)\\Inno Setup 5\\ISCC" Installer\\install_script_floppy_vs2003.iss 
				"""
			}
		}
		stage('Archive') {
			steps {
				archiveArtifacts artifacts: 'Installer\\Output\\Blocks3D_Setup_*,Installer\\Output\\B3DSTP*', fingerprint: true
			}
		}
	}
}
 

%undefine _disable_source_fetch

Name:      openfec
Version:   1.4.2.9
Release:   1%{?dist}
Summary:   Application-Level Forward Erasure Correction implementation library
License:   CeCILL-C and BSD
URL:       https://github.com/roc-streaming/openfec
Source:    %{URL}/archive/v%{version}/%{name}_%{version}.tar.gz
Provides:  %{name} = %{version}
Obsoletes: %{name} < %{version}

BuildRequires: cmake
BuildRequires: gcc
BuildRequires: coreutils
BuildRequires: findutils

%description
Application-Level Forward Erasure Correction implementation library

%package -n %{name}-devel
Summary:   Application-Level Forward Erasure Correction implementation library
Group:     Development/Libraries/C and C++
Provides:  %{name}-devel = %{version}
Requires:  %{name} = %{version}
Obsoletes: %{name}-devel < %{version}

%description -n %{name}-devel
Development package for Application-Level Forward Erasure Correction implementation library

%prep
%setup -n %{name}-%{version}

%build
%cmake
%cmake_build

%install
%cmake_install

%post   -n %{name} -p /sbin/ldconfig
%postun -n %{name} -p /sbin/ldconfig

%files -n %{name}
%license LICENCE_CeCILL-C_V1-en.txt
%license Licence_CeCILL_V2-en.txt
%{_libdir}/libopenfec.so.*

%files -n %{name}-devel
%license LICENCE_CeCILL-C_V1-en.txt
%license Licence_CeCILL_V2-en.txt
%{_includedir}/openfec
%{_datadir}/pkgconfig/openfec.pc
%{_libdir}/libopenfec.so

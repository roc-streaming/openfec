%global         __os_install_post \
  /usr/lib/rpm/brp-compress \
  /usr/lib/rpm/brp-strip \
  /usr/lib/rpm/brp-suse
%undefine       _disable_source_fetch
%define         major 1.4.2
%define         minor 4
%define         pkgname openfec
Name:           lib%{pkgname}
Version:        %{major}.%{minor}
Release:        6%{?dist}
Summary:        Application-Level Forward Erasure Correction implementation library

License:        CeCCIL-C_V1 AND CeCILL_V2
URL:            http://openfec.org
Source:         https://github.com/roc-project/openfec/archive/v%{version}.tar.gz
Provides:       %{name} = %{version}
Obsoletes:      %{name} < %{version}
BuildRequires:  cmake

%description
Application-Level Forward Erasure Correction implementation library

%package -n %{name}-devel
Summary:        Application-Level Forward Erasure Correction implementation library
Group:          Development/Libraries/C and C++
Provides:       %{name}-devel = %{version}
Requires:       %{name} = %{version}
Obsoletes:      %{name}-devel < %{version}

%description -n %{name}-devel
Development package for Application-Level Forward Erasure Correction implementation library

%prep
%setup -n %{pkgname}-%{version}

%build
%cmake
%cmake_build

%install
mkdir -p %{buildroot}/%{_bindir} \
        %{buildroot}/%{_libdir}/pkgconfig \
        %{buildroot}/%{_includedir}/%{pkgname}
for f in bin/Rel*/{eperftool,simple_*,test_*}; do
  install ${f} %{buildroot}/%{_bindir}/
done
install bin/Rel*/%{name}.so.%{major} %{buildroot}/%{_libdir}/
install build/pc/%{pkgname}.pc %{buildroot}/%{_libdir}/pkgconfig/
ln -s %{_libdir}/%{name}.so.1 %{buildroot}/%{_libdir}/%{name}.so
ln -s %{_libdir}/%{name}.so.%{major} %{buildroot}/%{_libdir}/%{name}.so.1
(cd src; find . -name '*.h' -exec cp -pr --parents {} %{buildroot}/%{_includedir}/%{pkgname} \;)

%post   -n %{name} -p /sbin/ldconfig
%postun -n %{name} -p /sbin/ldconfig

%files -n %{name}
%defattr(755,root,root)
%attr(644,root,root) %license LICENCE_CeCILL-C_V1-en.txt
%attr(644,root,root) %license Licence_CeCILL_V2-en.txt
%{_bindir}/*
%{_libdir}/%{name}.so*

%files -n %{name}-devel
%defattr(644,root,root)
%license LICENCE_CeCILL-C_V1-en.txt
%license Licence_CeCILL_V2-en.txt
%{_libdir}/pkgconfig/*
%{_includedir}/%{pkgname}/*

%changelog
* Tue Jun 28 2022 twojstaryzdomu - 1.4.2.4-6
- Updated attributes
- Removed committed pkgconfig patch
* Tue Feb  1 2022 twojstaryzdomu - 1.4.2.4-5
- Added pkgconfig template patch
- Use cmake rpm macros

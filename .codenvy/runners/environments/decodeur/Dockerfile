#
# Copyright (c) 2012-2015 Codenvy, S.A.
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#
# Contributors:
#   Codenvy, S.A. - initial API and implementation
#

FROM codenvy/cpp
ENV CODENVY_APP_BIND_DIR /home/user/app
VOLUME ["/home/user/app"]
CMD cd /home/user/app/src && \
    make decodeur && ./decodeur.e
